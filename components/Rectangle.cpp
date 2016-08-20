//
// Created by cod3r on 20/08/2016.
//

#include <GL/glew.h>
#include "Rectangle.h"

Rectangle::Rectangle(GLfloat color[]) {
    GLfloat vertices[] = {
            // Positions         // Colors
            0.2f, 0.2f, 0.0f,   color[0], color[1], color[2],  // Bottom Right
            -0.2f, -0.2f, 0.0f,   color[0], color[1], color[2],  // Bottom Left
            -0.2f,  0.2f, 0.0f,   color[0], color[1], color[2],   // Top
            // Second triangle
            0.2f,  0.2f, 0.0f,   color[0], color[1], color[2],
            -0.2f,  -0.2f, 0.0f,   color[0], color[1], color[2],
            0.2f,  -0.2f, 0.0f,   color[0], color[1], color[2]
    };
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // unbind VAO
}

void Rectangle::render() {
    this->myShader->use();

    glUniform1f(glGetUniformLocation(this->myShader->program, "xOffset"), this->xPos);
    glUniform1f(glGetUniformLocation(this->myShader->program, "YOffset"), this->yPos);

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

Shader Rectangle::shader() {
    return *this->myShader;
}

void Rectangle::shader(Shader* shader) {
    this->myShader = shader;
}

GLfloat Rectangle::x() {
    return this->xPos;
}

void Rectangle::x(GLfloat x) {
    this->xPos = x;
}

GLfloat Rectangle::y() {
    return this->yPos;
}

void Rectangle::y(GLfloat y) {
    this->yPos = y;
}