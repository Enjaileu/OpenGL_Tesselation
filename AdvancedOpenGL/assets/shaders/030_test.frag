#version 450 core

//flat in vec4 color;
in GS_OUT{
    vec4 color;
}fs_in;

out vec4 output_color;

void main(void)
{
    output_color = fs_in.color;
}