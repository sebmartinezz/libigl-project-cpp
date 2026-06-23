#version 330 core

out vec4 FragColor;

uniform float time;

void main()
{
    FragColor = vec4(abs(sin(time)), 0.2, 0.8, 1.0);
}