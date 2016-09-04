//
// Created by cod3r on 29/08/2016.
//

#ifndef GAME_SQUARE_H
#define GAME_SQUARE_H

#include "../util/Shader.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>

class Square {
    Shader* shaderPoint;
    GLuint VAO, VBO[2], EBO;
    GLfloat xPos = 0.0f, yPos = 0.0f, zPos = -1.0f;
    int windowWidth, windowHeight;
public:
    Square(int windowWidth, int windowHeight, GLfloat color[]);
    ~Square();
    void render();
    void shader(Shader* shader);
    void x(GLfloat x);
    void y(GLfloat y);
    void z(GLfloat z);
};


#endif //GAME_SQUARE_H
