// Tesselation Control Shader
#version 450 core

layout (vertices = 3) out;  // vertices = number of control point / patch

uniform float inner;
uniform float outer;

void main(void)
{
    // tesselation 0 controls the level of tesselation for the entire patch
    if(gl_InvocationID == 0) {
        gl_TessLevelInner[0] = 0.0;
        gl_TessLevelOuter[0] = 1.0;
        gl_TessLevelOuter[1] = 1.0;
        gl_TessLevelOuter[2] = 1.0;
    }
    // Now copy its input into its output with gl_out and gl_in
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}