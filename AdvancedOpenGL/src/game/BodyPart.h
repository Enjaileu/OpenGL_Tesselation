#ifndef BODYPART_H
#define BODYPART_H

#include "Cube.h"

class BodyPart :
    public Cube
{
public:
    BodyPart(float xP, float yP, float zP, CubeMesh* cubeMeshP, float uniScaleP);
    BodyPart() = default;

    ~BodyPart();

private:
    /* data */

};

#endif // BODYPART_H