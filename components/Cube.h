//
// Created by cod3r on 18/09/2016.
//

#ifndef GAME_CUBE_H
#define GAME_CUBE_H

#include "../util/Shader.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

class Cube {
    Shader* ShaderPoint;
    GLuint VAO, VBO[3], EBO, myTexture = 0;
    GLfloat xPos = 0.0f, yPos = 0.0f, zPos = -1.0f, myScale = 0.17f;
    int windowWidth, windowHeight;
public:
    Cube(int windowWidth, int windowHeight);
    Cube() {};
    void setupGL(int windowWidth, int windowHeight);
    void textureImage(unsigned char *image, int width, int height, GLenum format);
    void render();
    void shader(Shader* shader);
    void x(GLfloat x);
    void y(GLfloat y);
    void z(GLfloat z);
    void scale(GLfloat scale);
    ~Cube();
};


#endif //GAME_CUBE_H
