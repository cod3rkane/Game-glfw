#version 330 core
in vec3 Color;

out vec4 FragColor;

uniform vec4 ourColor;

void main() {
    FragColor = ourColor;
}