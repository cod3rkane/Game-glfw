//
// Created by cod3r on 24/08/2016.
//

#ifndef GAME_INPUTTEXT_H
#define GAME_INPUTTEXT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../util/Shader.h"
#include <GL/gl.h>
#include <ext.hpp>

using namespace std;

class InputText {
    static void cursorPositionCallBack(GLFWwindow*, double xpos, double ypos);
    static double mouseXpos, mouseYPos;
    GLuint VBO[2], VAO, EBO;
    Shader shader = Shader("assets/Shaders/ColorAndPosition.vert", "assets/Shaders/ColorAndPosition.frag");
    GLuint myTexture = 0;
    GLfloat xPos = 0.0f;
    GLfloat yPos = 0.0f;
    GLfloat zPos = 0.0f;
public:
    InputText(GLFWwindow* window);
    ~InputText();
    void render();
    void x(GLfloat xpos);
    void y(GLfloat ypos);
    void z(GLfloat zpos);
};


#endif //GAME_INPUTTEXT_H
