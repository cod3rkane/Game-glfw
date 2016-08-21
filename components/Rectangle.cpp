//
// Created by cod3r on 20/08/2016.
//

#include "Rectangle.h"

Rectangle::Rectangle(GLfloat color[]) {
    GLfloat vertices[] = {
        // Positions          // Colors                      // Texture Coords
        0.2f,  0.2f, 0.0f,   color[0], color[1], color[2],   1.0f, 1.0f, // Top Right
        0.2f, -0.2f, 0.0f,   color[0], color[1], color[2],   1.0f, 0.0f, // Bottom Right
        -0.2f, -0.2f, 0.0f,  color[0], color[1], color[2],   0.0f, 0.0f, // Bottom Left
        -0.2f,  0.2f, 0.0f,  color[0], color[1], color[2],   0.0f, 1.0f  // Top Left
    };

    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // Texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // unbind VAO
}

void Rectangle::render() {
    this->myShader->use();

    // Bind myTexture using myTexture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->myTexture);
    glUniform1i(glGetUniformLocation(this->myShader->program, "ourTexture1"), 0);

    glUniform1f(glGetUniformLocation(this->myShader->program, "xOffset"), this->xPos);
    glUniform1f(glGetUniformLocation(this->myShader->program, "YOffset"), this->yPos);

    glm::mat4 transform;
    transform = glm::translate(transform, glm::vec3(this->xPos, this->yPos, this->zPos));

    // Get matrix's uniform location and set matrix
    GLint transformLoc = glGetUniformLocation(this->myShader->program, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

GLuint Rectangle::texture() {
    return this->myTexture;
}

void Rectangle::textureImage(unsigned char *image, int width, int height) {
    try {
        // Load and create myTexture
        glGenTextures(1, &this->myTexture);
        glBindTexture(GL_TEXTURE_2D, this->myTexture);
        // Set out myTexture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Set myTexture filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        // Free memory image
        SOIL_free_image_data(image);
        glBindTexture(GL_TEXTURE_2D, 0);
    } catch (unsigned char *image) {
        cout << "couldn't load image because: " << image << endl;
        throw "Error";
    } catch (int num) {
        cout << "couldn't load image because: " << num << endl;
        throw "Error";
    }
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

GLfloat Rectangle::z() {
    return this->zPos;
}

void Rectangle::z(GLfloat z) {
    this->zPos = z;
}

Rectangle::~Rectangle() {
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
}