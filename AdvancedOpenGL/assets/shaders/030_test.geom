#version 450 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 12) out;

uniform float mix_amount;

out GS_OUT{
    vec4 color;
} gs_out;
//flat out vec4 color;

uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;

void make_face(vec3 a, vec3 b, vec3 c, vec4 color)
{
    vec3 face_normal = normalize(cross(c - a, c - b));

    gl_Position = mvpMatrix * vec4(a, 1.0);
    vec4 colorT = vec4(normalize(gl_Position.x), normalize(gl_Position.y), normalize(gl_Position.z), 1.0)* (-1*(mat3(mvMatrix) * face_normal).z);
    gs_out.color = colorT;
    EmitVertex();

    gl_Position = mvpMatrix * vec4(b, 1.0);
    colorT = vec4(normalize(gl_Position.x), normalize(gl_Position.y), normalize(gl_Position.z), 1.0)* (-1*(mat3(mvMatrix) * face_normal).z);
    gs_out.color = colorT;
    EmitVertex();

    gl_Position = mvpMatrix * vec4(c, 1.0);
    colorT = vec4(normalize(gl_Position.x), normalize(gl_Position.y), normalize(gl_Position.z), 1.0)* (-1*(mat3(mvMatrix) * face_normal).z);
    gs_out.color = colorT;
    EmitVertex();

    EndPrimitive();
}

void main(void)
{
    int n;
    vec3 a = gl_in[0].gl_Position.xyz;
    vec3 b = gl_in[1].gl_Position.xyz;
    vec3 c = gl_in[2].gl_Position.xyz;

    vec3 d = (a + b) * 0.5;
    vec3 e = (b + c) * 0.5;
    vec3 f = (c + a) * 0.5;

    vec3 aSphere = normalize(a);
    a = mix(a, aSphere, mix_amount);
    vec3 bSphere = normalize(b);
    b = mix(b, bSphere, mix_amount);
    vec3 cSphere = normalize(c);
    c = mix(c, cSphere, mix_amount);
    vec3 dSphere = normalize(d);
    d = mix(d, dSphere, mix_amount);
    vec3 eSphere = normalize(e);
    e = mix(e, eSphere, mix_amount);
    vec3 fSphere = normalize(f);
    f = mix(f, fSphere, mix_amount);

    vec4 color1 = vec4(0.063, 0.08, 0.29, 1.0);
    vec4 color2 = vec4(0.8314, 0.5647, 0.102, 1.0);

    make_face(a, d, f, color1);
    make_face(d, b, e, color1);
    make_face(e, c, f, color2);
    make_face(d, e, f, color2);

    EndPrimitive();
}