#version 430 core

layout (location = 0) in vec2 VertexPosition;
layout (location = 1) in vec3 VertexColor;

uniform mat4 projection;

out vec3 Color;

void main() {
    gl_Position = projection * vec4(VertexPosition.xy, 0.0, 1.0);
    Color = VertexColor;
}