#include "Scene_030_Test.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_030_Test::Scene_030_Test(): totalTime(0) {

}

Scene_030_Test::~Scene_030_Test() {
    clean();
}

void Scene_030_Test::setGame(Game *_game) {
    game = _game;
}

void Scene_030_Test::clean() {
    glDeleteVertexArrays(1, &vao);
}

void Scene_030_Test::pause() {
}

void Scene_030_Test::resume() {
}

void Scene_030_Test::handleEvent(const InputState &inputState) {

}

void Scene_030_Test::load() {
    
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), SHADER_TECS(SHADER_NAME), SHADER_TESE(SHADER_NAME), SHADER_GEOM(SHADER_NAME), SHADER_ID(SHADER_NAME));


    static const GLfloat vertices[] =
    {
        0.500f,  -0.500f, 0.500f,
        -0.500f, -0.500f, 0.500f,
        0.500f,  0.500f, 0.500f,
        -0.500f, 0.500f, 0.500f,
        -0.500f, -0.500f, -0.500f,
        0.500f, -0.500f, -0.500f,
        -0.500f, 0.500f, -0.500f,
        0.500f, 0.500f, -0.500f,
    };

    static const GLushort indices[] =
    {
        //face 1
        1, 0, 2,
        1, 2, 3,
        //face 2
        2, 0, 7,
        7, 0, 5,
        //face 3
        7, 5, 6,
        6, 5, 4,
        //face 4
        6, 4, 3,
        3, 4, 1,
        //face 5
        6, 3, 7,
        7, 3, 2,
        //face6
        1, 4, 0,
        0, 4, 5
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer); // GL_ELEMENT_ARRAY_BUFFER = vertex array indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices) + sizeof(indices), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), sizeof(vertices), vertices);

    glBindBuffer(GL_ARRAY_BUFFER, buffer); // GL_ARRAY_BUFFER = vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)sizeof(indices)); // Define an array of generic vertex attributes data
    glEnableVertexAttribArray(0);

    // glEnable(GL_CULL_FACE);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_POINT  GL_LINE  GL_FILL

    shader = Assets::getShader(SHADER_ID(SHADER_NAME));
}

void Scene_030_Test::update(float dt) {
    totalTime += dt;
}

void Scene_030_Test::draw()
{
    // Variables init =======================
    static const GLfloat blue[] = {0.05f, 0.25f, 0.45f, 1.0f};
    static const GLfloat one = 1.0f;
    float f = totalTime * timeScale;

    // Variables update =====================
    float mix = abs(sin(f*10)); 
    
    // Buffer clear =========================
    glClearBufferfv(GL_COLOR, 0, blue);
    glClearBufferfv(GL_DEPTH, 0, &one);

    // Projections ==========================
    proj = Matrix4::createPerspectiveFOV(45.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);
    view = Matrix4::createTranslation(Vector3(0.0f, 0.0f, -4.0f)) *
                            Matrix4::createRotationY(f * 20.0f) *
                            Matrix4::createRotationX(f * 5.0f)
    ;

    shader.use();

    // Update geometry shader ===============
    shader.setMatrix4("mvpMatrix", proj * view);
    shader.setMatrix4("mvMatrix", view);
    shader.setFloat("mix_amount", mix);

    glPointSize(5.0f);
    glDrawElements(GL_PATCHES, 12*3, GL_UNSIGNED_SHORT, NULL);
}
