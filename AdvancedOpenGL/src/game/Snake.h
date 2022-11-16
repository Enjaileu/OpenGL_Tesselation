#ifndef SNAKE_H
#define SNAKE_H

#include "BodyPart.h"
#include <vector>

class Snake
{
public:
    Snake(float xP, float yP, float zP, float scaleP, float stepSizeP, float delayP, int segmentNbP, CubeMesh* headMeshP, CubeMesh* bodyPartMeshP);
    ~Snake();

    void createSnake();

    void load();
    void clean();
    void update();
    void draw(Shader& shaderP);

    Vector3 getMoveDirection() const { return moveDirection; };
    void setMoveDirection(Vector3 moveDirectionP);

    float getStepSize() const { return stepSize; };
    void setStepSize(float stepSizeP);

    float getDelay() const { return delay; };
    void setDelay(float delayP);

    void moveHead();
    void updateBodyPos();

    std::vector<BodyPart> getSnakeBody() const { return snakeBody; };

    void addBodySegment();

private:
    BodyPart snakeHead;
    std::vector<BodyPart> snakeBody;

    float x { 0.0f };
    float y { 0.0f };
    float z { 0.0f };

    float scale { 1.0f };

    Vector3 moveDirection { 1, 0, 0 };
    float stepSize { 1.0f };
    float delay { 1.0f };

    int segmentNb { 3 };
    
    CubeMesh* headMesh { nullptr };
    CubeMesh* bodyPartMeshP { nullptr };

    float timer { 0 };
};

#endif // SNAKE_H