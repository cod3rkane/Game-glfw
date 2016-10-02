//
// Created by cod3r on 10/1/16.
//

#include "Player.h"

Player::Player(int windowWidth, int windowHeight) {
    this->setWindowWidth(windowWidth);
    this->setWindowHeight(windowHeight);
    this->setupGL();
}

void Player::setupGL() {
    GLfloat vertices[] = {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,

            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,

            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f
    };

    GLfloat color[] = {
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,

            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,

            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,

            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,

            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,

            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88,
            0.20f, 0.25f, 0.88
    };

    GLuint indices[] = {
            0, 1, 3, // First Triangle
            1, 2, 3  // Second Triangle
    };

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(2, this->VBO);
    GLuint positionBufferHandle = this->VBO[0];
    GLuint colorBufferHandle = this->VBO[1];
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);

    // vertex Position
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // vertex Color
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Enable vertex attribute location
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

    glBindVertexArray(0); //unbind VAO
}

void Player::render() {
    try {
        this->ShaderPoint->use();
    } catch (GLuint e) {
        cout << "GLuint error on Use Cube::ShaderPoint" << endl;
    }

    glm::mat4 model, view, projection;
    view = this->camera.GetViewMatrix();
    projection = glm::perspective(this->camera.Zoom, (float)this->windowWidth / (float)this->windowHeight, 0.1f, 1000.0f);
    model = glm::scale(model, glm::vec3(this->Scale, this->Scale, this->Scale));

    // Get their uniform location
    GLint modelLoc = glGetUniformLocation(this->ShaderPoint->program, "model");
    GLint viewLoc = glGetUniformLocation(this->ShaderPoint->program, "view");
    GLint projectLoc = glGetUniformLocation(this->ShaderPoint->program, "projection");

    // pass them to the shaders
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(this->VAO);
//    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

Player::~Player() {
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(2, this->VBO);
    glDeleteBuffers(1, &this->EBO);
}

Shader *Player::getShaderPoint() const {
    return ShaderPoint;
}

void Player::setShaderPoint(Shader *ShaderPoint) {
    Player::ShaderPoint = ShaderPoint;
}

GLfloat Player::getXPos() const {
    return xPos;
}

void Player::setXPos(GLfloat xPos) {
    Player::xPos = xPos;
}

GLfloat Player::getYPos() const {
    return yPos;
}

void Player::setYPos(GLfloat yPos) {
    Player::yPos = yPos;
}

GLfloat Player::getZPos() const {
    return zPos;
}

void Player::setZPos(GLfloat zPos) {
    Player::zPos = zPos;
}

GLfloat Player::getScale() const {
    return Scale;
}

void Player::setScale(GLfloat Scale) {
    Player::Scale = Scale;
}

int Player::getWindowWidth() const {
    return windowWidth;
}

void Player::setWindowWidth(int windowWidth) {
    Player::windowWidth = windowWidth;
}

int Player::getWindowHeight() const {
    return windowHeight;
}

void Player::setWindowHeight(int windowHeight) {
    Player::windowHeight = windowHeight;
}

const Camera &Player::getCamera() const {
    return camera;
}

void Player::setCamera(const Camera &camera) {
    Player::camera = camera;
}
