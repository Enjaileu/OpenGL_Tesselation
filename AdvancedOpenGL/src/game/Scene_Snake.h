#ifndef Scene_Snake_H
#define Scene_Snake_H

#include "../engine/Scene.h"
// #include "../engine/Assets.h"

#include "Apple.h"
#include "Snake.h"

class Scene_Snake : public Scene {
public:
    Scene_Snake();
    ~Scene_Snake();
    void load();
    void clean();
    void pause();
    void resume();
    void handleEvent(const InputState &);
    void update(float dt);
    void draw();
    void setGame(Game *);

    bool collision(Cube cubeA, Cube cubeB);

    void spawnApple();

private:
    Game *game;

    Matrix4 projection;
    Shader shader;

    // Divergences from the Scene_008
    CubeMesh* cubeMesh;
    vector<Cube> cubes;

    Snake* snake;
    Vector3 snakeDirection { 1, 0, 0 };

    vector<Apple> apples;

    float maxDepth{-10.0f};

    int score { 0 };
};

#endif //Scene_Snake_H
