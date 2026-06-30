#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor; //ahora el color es dado por mesh

out vec3 vColor;

void main()
{
    vColor = aColor;
    gl_Position = vec4(aPos, 1.0);
}