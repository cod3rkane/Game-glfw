//
// Created by cod3r on 29/08/2016.
//

#include "Square.h"

Square::Square(int windowWidth, int windowHeight, GLfloat color[]) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    GLfloat vertices[] = {
        0.2f,  0.2f, 0.0f,
        0.2f, -0.2f, 0.0f,
        -0.2f, -0.2f, 0.0f,
        -0.2f,  0.2f, 0.0f
    };

    GLfloat myColor[] = {
            color[0], color[1], color[2],
            color[0], color[1], color[2],
            color[0], color[1], color[2],
            color[0], color[1], color[2]
    };

    GLuint indices[] = {
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(2, this->VBO);
    GLuint posititionBufferHandle = this->VBO[0];
    GLuint colorBufferHandle = this->VBO[1];
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);

    // Vertex Position
    glBindBuffer(GL_ARRAY_BUFFER, posititionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Vertex Color
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(myColor), myColor, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // enable vertex attribute location 0 Position
    glEnableVertexAttribArray(0); // Vertex Position
    glEnableVertexAttribArray(1); // Vertex Color

    glBindBuffer(GL_ARRAY_BUFFER, posititionBufferHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

//    glBindVertexArray(0); // unbind VAO
}

void Square::render() {
    glDisable(GL_DEPTH_TEST);
    try {
        this->shaderPoint->use();
    } catch (GLuint e) {
        cout << "GLuint error on Use Square::shaderPoint" << endl;
    }

    glm::mat4 model, view, projection;
//    model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::translate(view, glm::vec3(this->xPos, this->yPos, this->zPos));
    projection = glm::perspective(45.0f, (GLfloat)this->windowWidth / this->windowHeight, 0.1f, 100.0f);

    // Get their uniform location
    GLint modelLoc = glGetUniformLocation(this->shaderPoint->program, "model");
    GLint viewLoc = glGetUniformLocation(this->shaderPoint->program, "view");
    GLint projectLoc = glGetUniformLocation(this->shaderPoint->program, "projection");

    // pass them to the shaders
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);
}

void Square::shader(Shader *shader) {
    this->shaderPoint = shader;
}

void Square::x(GLfloat x) {
    this->xPos = x;
}

void Square::y(GLfloat y) {
    this->yPos = y;
}

void Square::z(GLfloat z) {
    this->zPos = z;
}

Square::~Square() {glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(2, this->VBO);
    glDeleteBuffers(1, &this->EBO);
}