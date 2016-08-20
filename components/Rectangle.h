//
// Created by cod3r on 20/08/2016.
//

#ifndef GAME_RECTANGLE_H
#define GAME_RECTANGLE_H


#include <GL/gl.h>
#include "../util/Shader.h"

class Rectangle {
    GLuint VBO, VAO;
    Shader* myShader;
    GLfloat xPos = 0.0f;
    GLfloat yPos = 0.0f;
public:
    Rectangle(GLfloat color[]);
    void render();
    Shader shader();
    void shader(Shader* shader);
    GLfloat x();
    void x(GLfloat x);
    GLfloat y();
    void y(GLfloat y);
};

#endif //GAME_RECTANGLE_H
