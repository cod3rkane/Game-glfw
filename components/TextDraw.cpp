//
// Created by cod3r on 21/08/2016.
//

#include "TextDraw.h"

TextDraw::TextDraw(Shader *shader, int windowWidth, int windowHeight) {
    this->myShader = shader;
    this->windowW = windowWidth;
    this->windowH = windowHeight;

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->windowW), 0.0f,
                                      static_cast<GLfloat>(this->windowH));
    this->myShader->use();
    glUniformMatrix4fv(glGetUniformLocation(this->myShader->program, "projection"), 1, GL_FALSE,
                       glm::value_ptr(projection));

    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Shader *TextDraw::shader() {
    return this->myShader;
}

void TextDraw::shader(Shader *shader) {
    this->myShader = shader;
}

string TextDraw::text() {
    return this->Text;
}

void TextDraw::text(string text) {
    this->Text = text;
}

GLfloat TextDraw::x() {
    return this->X;
}

void TextDraw::x(GLfloat x) {
    this->X = x;
}

GLfloat TextDraw::y() {
    return this->Y;
}

void TextDraw::y(GLfloat y) {
    this->Y = y;
}

GLfloat TextDraw::scale() {
    return this->Scale;
}

void TextDraw::scale(GLfloat scale) {
    this->Scale = scale;
}

glm::vec3 TextDraw::color() {
    return this->Color;
}

void TextDraw::color(glm::vec3 color) {
    this->Color = color;
}

map<GLchar, Character> TextDraw::characters() {
    return this->Characters;
}

void TextDraw::characters(map<GLchar, Character> characters) {
    this->Characters = characters;
}

void TextDraw::render() {
    // Activate corresponding render state
    this->myShader->use();
    try {
        glUniform3f(glGetUniformLocation(this->myShader->program, "textColor"), this->Color.x, this->Color.y, this->Color.z);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(this->VAO);
    } catch (int err) {
        cout << "ERROR:: When get UniformLocation: " << err << endl;
    }

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = this->Text.begin(); c != this->Text.end(); c++) {
        Character ch = this->Characters[*c];

        GLfloat xpos = this->X + ch.Bearing.x * this->Scale;
        GLfloat ypos = this->Y - (ch.Size.y - ch.Bearing.y) * this->Scale;

        GLfloat w = ch.Size.x * this->Scale;
        GLfloat h = ch.Size.y * this->Scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
                {xpos,     ypos + h, 0.0, 0.0},
                {xpos,     ypos,     0.0, 1.0},
                {xpos + w, ypos,     1.0, 1.0},

                {xpos,     ypos + h, 0.0, 0.0},
                {xpos + w, ypos,     1.0, 1.0},
                {xpos + w, ypos + h, 1.0, 0.0}
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        this->X += (ch.Advance >> 6) * this->Scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

TextDraw::~TextDraw() {
    /**
     * Clean Objects Array
     */
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
}