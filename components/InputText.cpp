//
// Created by cod3r on 24/08/2016.
//

#include "InputText.h"

double InputText::mouseXpos = 0.0f;
double InputText::mouseYPos = 0.0f;

InputText::InputText(GLFWwindow* window, int windowWidth, int windowHeight) {
    this->windowW = windowWidth;
    this->windowH = windowHeight;
    // Set cursor position callback
    glfwSetCursorPosCallback(window, this->cursorPositionCallBack);
    GLfloat positionData[] = {
            0.2f, 0.2f,
            0.2f, -0.2f,
            -0.2f, -0.2f,
            -0.2f, 0.2f
    };

    GLfloat colorData[] = {
            0.66f, 0.04f, 0.83f,
            0.66f, 0.04f, 0.83f,
            0.66f, 0.04f, 0.83f,
            0.66f, 0.04f, 0.83f
    };

    // Create and set-up the vertex array object
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    // Buffer Object
    glGenBuffers(2, this->VBO);
    GLuint positionBufferHandle = this->VBO[0];
    GLuint colorBufferHandle = this->VBO[1];

    // Create and set-up the Element Buffer object
    glGenBuffers(1, &this->EBO);
    GLuint indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    // Populate position Buffer
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW);

    // Populate color buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);

    // set-up EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Enable the vertex attribute array
    glEnableVertexAttribArray(0); // Position
    glEnableVertexAttribArray(1); // Color

    // Map index 0 to the position buffer
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (GLvoid*)0);

    // Map index 1 to the color buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)0);
}

/**
 * Receive the cursor position and assign Y and X position
 * @param xpos
 * @param ypos
 */
void InputText::cursorPositionCallBack(GLFWwindow *, double xpos, double ypos) {
//    cout << "Mouse Xpos: " << xpos << endl;
//    cout << "Mouse YPos: " << ypos << endl;
    InputText::mouseXpos = xpos;
    InputText::mouseYPos = ypos;
}

void InputText::render() {
    /**
     * Convert x,y position in x,y projection position. Example X = 1280 in 1.0 or Window full width in 1.0 a 0.0
     */
    cout << "X: " << this->mouseXpos * (2.0 / this->windowW) - 1.0 << endl;
    cout << "Y: " << this->mouseYPos * (2.0 / this->windowH) - 1.0 << endl;
    this->shader.use();
    // set-up transform
    glm::mat4 projection;
    projection = glm::translate(projection, glm::vec3(this->xPos, this->yPos, 0.0f));

    // Get Matrix's uniform location and set matrix
    GLint projectionLoc = glGetUniformLocation(this->shader.program, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void InputText::x(GLfloat xpos) {
    this->xPos = xpos;
}

void InputText::y(GLfloat ypos) {
    this->yPos = ypos;
}

InputText::~InputText() {
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(2, &this->VBO[0]);
    glDeleteBuffers(1, &this->VBO[1]);
    glDeleteBuffers(1, &this->EBO);
}