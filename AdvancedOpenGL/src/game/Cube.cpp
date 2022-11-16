#include "Cube.h"

#include "CubeMesh.h"
#include "../engine/Shader.h"

Cube::Cube(float xP, float yP, float zP, CubeMesh* cubeMeshP, float uniScaleP) :
    x { xP }, y { yP }, cubeMesh { cubeMeshP }, uniformScale {uniScaleP}
{
    setPosition(xP, yP, zP);
}

Cube::~Cube(){
}

void Cube::load(){
}

void Cube::clean(){
}

void Cube::update(){

}

void Cube::draw(Shader& shader){
    shader.setMatrix4("mv_matrix", transform);
    cubeMesh->draw();
}

void Cube::setUniformScale(float scaleP) {
    uniformScale = scaleP;

    transform = computeTransform();
}

void Cube::setPosition(float xP, float yP, float zP) {
    x = xP;
    y = yP;
    z = zP;

    transform = computeTransform();
}

Matrix4 Cube::computeTransform() {
    return Matrix4::createTranslation(Vector3(x, y, z))
         * Matrix4::createScale(uniformScale);
}