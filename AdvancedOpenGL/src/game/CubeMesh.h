#ifndef CUBEMESH_H
#define CUBEMESH_H

#include <GL/glew.h>

class CubeMesh
{
public:
    CubeMesh();
    ~CubeMesh();

    void load();
    void draw();
    void clean();

private:
    GLuint vao;
    GLuint buffer; 
};

#endif // CUBEMESH_H