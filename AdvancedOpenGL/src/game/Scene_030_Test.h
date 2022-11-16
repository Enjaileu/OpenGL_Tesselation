#ifndef Scene_030_Test_H
#define Scene_030_Test_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"
#include "../engine/MeshObject.h"

class Scene_030_Test : public Scene {
public:
    Scene_030_Test();
    ~Scene_030_Test();
    void load();
    void clean();
    void pause();
    void resume();
    void handleEvent(const InputState &);
    void update(float dt);
    void draw();
    void setGame(Game *);

private:
    Game *game;
    GLuint vao;
    GLuint buffer;
    float totalTime;
    const float timeScale = 0.05f;

    bool tesselation{ true };

    // Uniforms
    Matrix4 mvp;
    Matrix4 view;
    Matrix4 proj;
    float innerLength{ 5.0f };
    float innerWidth{ 5.0f };
    float outerWidth{ 5.0f };
    float outerLength{ 5.0f };

    Shader shader;
};


#endif //Scene_030_Test_H
