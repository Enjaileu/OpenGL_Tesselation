#ifndef Cube_H
#define Cube_H

#include "../engine/Assets.h"
#include "../engine/maths/Matrix4.h"

class CubeMesh;
class Shader;

class Cube
{
public:
    Cube() = default;
    Cube(float xP, float yP, float zP, CubeMesh* cubeMeshP, float uniScaleP = 1.0f);
    ~Cube();
    void load();
    void clean();
    void update();
    void draw(Shader& shaderP);

    //v Transform ===========================================
    float getUniformScale() const { return uniformScale; };
    void setUniformScale(float scaleP);

    float getXPos() const { return x; };
    float getYPos() const { return y; };
    float getZPos() const { return z; };
    void setPosition(float xP, float yP, float zP);

    float getXRot() const { return xRot; };
    float getYRot() const { return yRot; };
    float getZRot() const { return zRot; };
    void setRotation(float xRotP, float yRotP, float zRotP);

    float getWidth() const { return uniformScale*0.25f; };
    float getHeight() const { return uniformScale*0.25f; };

    Matrix4 computeTransform();
    //^ Transform ===========================================

protected:
    GLuint buffer;

    //v Transform ===========================================
    float uniformScale { 1.0f };

    float x { 0.0f };
    float y { 0.0f };
    float z { -4.0f };

    float xRot { 0.0f };
    float yRot { 0.0f };
    float zRot { 0.0f };

    Matrix4 transform;
    //^ Transform ===========================================

    CubeMesh* cubeMesh { nullptr };
};

#endif //Cube_H