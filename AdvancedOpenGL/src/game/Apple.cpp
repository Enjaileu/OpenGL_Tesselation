#include "Apple.h"
#include "../engine/Timer.h"

#include "CubeMesh.h"

#include <cstdlib>
#include <ctime>

Apple::Apple(float xP, float yP, float zP, CubeMesh* cubeMeshP, float uniScaleP, float zRotSpeedP):
    Cube(xP, yP,zP,cubeMeshP,uniScaleP), zRotSpeed {zRotSpeedP}
{
    setPosition(xP, yP, zP);
    setZRotation(1.0f);
}

Apple::~Apple()
{
}

void Apple::update() {
    const float t = Timer::getTimeSinceStart() * 0.3f;

    // Auto z sinusoidal translation
    float zTranslation = Maths::sin(5.f * t) * 0.5f;
    //                              ^ speed     ^ magnitude
    // Auto rotation
    float autoRot = zRotSpeed * t * Maths::toRadians(zRot);
    // Auto movement
    transform = Matrix4::createTranslation(Vector3(x, y, z + zTranslation)) 
              * Matrix4::createScale(uniformScale)
              * Matrix4::createRotationZ(autoRot);
}

void Apple::setZRotation(float zRotP) {
    zRot = zRotP;

    transform = computeTransform();
}

Matrix4 Apple::computeTransform() {
    return Matrix4::createTranslation(Vector3(x, y, z))
         * Matrix4::createScale(uniformScale)
         * Matrix4::createRotationZ(zRot);
}
