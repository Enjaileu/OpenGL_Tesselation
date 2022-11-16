#include "Scene_Snake.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>

#include "CubeMesh.h"

Scene_Snake::Scene_Snake() {
}

Scene_Snake::~Scene_Snake() {
    clean();
}

void Scene_Snake::setGame(Game *_game) {
    game = _game;
}

void Scene_Snake::load() {
    std::srand((int) std::time(nullptr));
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", "", SHADER_ID(SHADER_NAME));
    projection = Matrix4::createPerspectiveFOV(70.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);

    cubeMesh = new CubeMesh();
    cubeMesh->load();

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    shader = Assets::getShader(SHADER_ID(SHADER_NAME));

    //v Load snake and apples ===============================
    // Snake parts
    snake = new Snake(-5.0f, 0.0f, maxDepth, 1.0f, 0.5f, 0.25f, 2, cubeMesh, cubeMesh);

    // Apples
    apples.emplace_back(.0f, .0f, maxDepth, cubeMesh, .5f, 150.0f);
    apples.emplace_back(2.0f, 2.0f, maxDepth, cubeMesh, .5f, 150.0f);
    //^ Load snake and apples ===============================
}

void Scene_Snake::clean() {
    cubeMesh->clean();
    delete cubeMesh;

    delete snake;
}

void Scene_Snake::pause() {
}

void Scene_Snake::resume() {
}

void Scene_Snake::handleEvent(const InputState &inputState) {
    if (inputState.keyboardState.isJustPressed(SDL_SCANCODE_A) || inputState.keyboardState.isJustPressed(SDL_SCANCODE_LEFT)) {
        snakeDirection = Vector3( -1, 0, 0 );
        snake->setMoveDirection(snakeDirection);
    } 
    else if (inputState.keyboardState.isJustPressed(SDL_SCANCODE_D) || inputState.keyboardState.isJustPressed(SDL_SCANCODE_RIGHT)) {
        snakeDirection = Vector3( 1, 0, 0 );
        snake->setMoveDirection(snakeDirection);
    } 
    else if (inputState.keyboardState.isJustPressed(SDL_SCANCODE_W) || inputState.keyboardState.isJustPressed(SDL_SCANCODE_UP)) {
        snakeDirection = Vector3( 0, 1, 0 );
        snake->setMoveDirection(snakeDirection);
    } 
    else if (inputState.keyboardState.isJustPressed(SDL_SCANCODE_S) || inputState.keyboardState.isJustPressed(SDL_SCANCODE_DOWN)) {
        snakeDirection = Vector3( 0, -1, 0 );
        snake->setMoveDirection(snakeDirection);
    } 
}

void Scene_Snake::update(float dt) {
    //v Movements ==================================
    // Ref this code with a pointer to only use one loop
    for (auto& cube : cubes)
    {
        cube.update();
    }
    for (auto& apple : apples)
    {
        apple.update();
    }
    snake->update();
    //^ Movements ==================================
    //v Test collisions ============================
    // Get the snake body
    vector<BodyPart> snakeBody = snake->getSnakeBody();
    // Get the snake head
    BodyPart snakeHead = snakeBody[0];
    // Collision against a body part ======
    bool doesHeadCollidesBody = false;

    for (int i = 2; i < snakeBody.size(); i++)
    {
        doesHeadCollidesBody = collision(snakeHead, snakeBody[i]);
    }
    if (doesHeadCollidesBody) {
        std::cout << "test";
    }

    // Collision against an apple =========
    bool doesHeadCollidesApple = false;
    int appleId = -1;

    for (int i = 0; i < apples.size(); i++)
    {
        doesHeadCollidesApple = collision(snakeHead, apples[i]);

        if (doesHeadCollidesApple) {
            appleId = i;

            break;
        }
    }
    if (appleId != -1) {
        // Add one point
        score++;

        // Delete apple
        apples.erase(apples.begin() + appleId);
        // Prepare constraints
        float constrX = 6;
        float constrY = 4;
        float appleXPos = -constrX + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(constrX+constrX)));;
        float appleYPos = -constrY + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(constrY+constrY)));;
        // Spawn a new apple
        apples.emplace_back(appleXPos, appleYPos, maxDepth, cubeMesh, 0.5f, 150.0f);
        // Add a segment
        snake->addBodySegment();
        // Improve speed!
        snake->setDelay(snake->getDelay()*.975f);
    }

    // Collision against a wall ===========


    //^ Test collisions ============================
}

void Scene_Snake::draw()
{
    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);

    shader.use();
    shader.setMatrix4("proj_matrix", projection);

    snake->draw(shader);

    for (auto& cube : cubes)
    {
        cube.draw(shader);
    }
    for (auto& apple : apples)
    {
        apple.draw(shader);
    }        
}

bool Scene_Snake::collision(Cube cubeA, Cube cubeB) {
    float cubeAminX = cubeA.getXPos() - cubeA.getWidth();
    float cubeAmaxX = cubeA.getXPos() + cubeA.getWidth();
    float cubeAminY = cubeA.getYPos() - cubeA.getHeight();
    float cubeAmaxY = cubeA.getYPos() + cubeA.getHeight();

    float cubeBminX = cubeB.getXPos() - cubeB.getWidth();
    float cubeBmaxX = cubeB.getXPos() + cubeB.getWidth();
    float cubeBminY = cubeB.getYPos() - cubeB.getHeight();
    float cubeBmaxY = cubeB.getYPos() + cubeB.getHeight();

    return (cubeBmaxX >= cubeAminX && cubeBmaxX <= cubeAmaxX && cubeBminY >= cubeAminY && cubeBminY <= cubeAmaxY )
    || (cubeBminX >= cubeAminX && cubeBminX <= cubeAmaxX && cubeBminY >= cubeAminY && cubeBminY <= cubeAmaxY )
    || (cubeBminX >= cubeAminX && cubeBminX <= cubeAmaxX && cubeBmaxY <= cubeAmaxY && cubeBmaxY >= cubeAminY)
    || (cubeBmaxX >= cubeAminX && cubeBmaxX <= cubeAmaxX && cubeBmaxY >= cubeAminY && cubeBmaxY <= cubeAmaxY);
}