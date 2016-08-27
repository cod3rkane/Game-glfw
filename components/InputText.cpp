//
// Created by cod3r on 24/08/2016.
//

#include "InputText.h"

// Initialize Static Properties.
double InputText::mouseXpos = 0.0f;
double InputText::mouseYPos = 0.0f;
int InputText::windowW = 0;
int InputText::windowH = 0;

InputText::InputText(GLFWwindow *window, int windowWidth, int windowHeight) {
    this->windowW = windowWidth;
    this->windowH = windowHeight;
    // Set cursor position callback
    glfwSetCursorPosCallback(window, this->cursorPositionCallBack);
    GLfloat positionData[] = {
            this->xScale, this->yScale,
            this->xScale, -this->yScale,
            -this->xScale, -this->yScale,
            -this->xScale, this->yScale
    };

    GLfloat colorData[] = {
            0.50f, 0.49f, 0.49f,
            0.50f, 0.49f, 0.49f,
            0.50f, 0.49f, 0.49f,
            0.50f, 0.49f, 0.49f
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
            0, 2, 3,
            0, 2, 1
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
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (GLvoid *) 0);

    // Map index 1 to the color buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid *) 0);
}

/**
 * Receive the cursor position and assign Y and X position
 * @param xpos
 * @param ypos
 */
void InputText::cursorPositionCallBack(GLFWwindow *, double xpos, double ypos) {
//    cout << "Mouse Xpos: " << xpos << endl;
//    cout << "Mouse YPos: " << ypos << endl;
    /**
     * Convert x,y position in x,y projection position. Example X = 1280 in 1.0 or Window full width in 1.0 a 0.0
     */
    InputText::mouseXpos = xpos * (2.0f / InputText::windowW) - 1.0f;
    /**
     * When mouse in top Y need to negative number. For fixed this add * -1
     */
    InputText::mouseYPos = (ypos * (2.0f / InputText::windowH) - 1.0f) * -1;
}

void InputText::render() {
    this->mouseOver();
    this->shader.use();

    // set-up color
    GLint vertexColorLocation = glGetUniformLocation(this->shader.program, "ourColor");
    glUniform4f(vertexColorLocation, 0.50f, 0.49f, 0.49f, this->opacity);

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

/**
 * Check if mouse is above of element.
 */
void InputText::mouseOver() {
    if ((this->mouseYPos >= (this->yPos - this->yScale) && this->mouseYPos <= (this->yPos + this->yScale)) &&
        (this->mouseXpos >= (this->xPos - this->xScale) && this->mouseXpos <= (this->xPos + this->xScale))) {
        this->opacity = 0.6f;
    } else {
        this->opacity = 1.0f;
    }
}

InputText::~InputText() {
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(2, &this->VBO[0]);
    glDeleteBuffers(1, &this->VBO[1]);
    glDeleteBuffers(1, &this->EBO);
}