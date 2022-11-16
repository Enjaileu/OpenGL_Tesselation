#ifndef APPLE_H
#define APPLE_H

#include "Cube.h"

class Apple: 
    public Cube
{
public:
    Apple(float xP, float yP, float zP, CubeMesh* cubeMeshP, float uniScaleP = 1.0f, float zRotSpeedP = 0.0f);
    ~Apple();

    void update();

    // void draw(Shader& shader);

    //v Auto rotation =======================================
    float getZRotSpeed() { return zRotSpeed; };
    void setZRotSpeed(float zRotSpeedP);

    void setZRotation(float zRotP);

    Matrix4 computeTransform();
    //^ Auto rotation =======================================
    //v Interactions ========================================

    //^ Interactions ========================================

private:
    float zRotSpeed { 0.0f };

};

#endif // APPLE_H