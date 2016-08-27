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
#include <list>

using namespace std;

class InputText {
    static void cursorPositionCallBack(GLFWwindow*, double xpos, double ypos);
    static double mouseXpos, mouseYPos;
    static int windowW, windowH;
    GLuint VBO[2], VAO, EBO;
    Shader shader = Shader("assets/Shaders/Color-Position-Projection.vert", "assets/Shaders/Color-Position-Projection.frag");
    GLfloat xPos = 0.0f;
    GLfloat yPos = 0.0f;
    GLfloat xScale = 0.3f;
    GLfloat yScale = 0.04f;
    GLfloat opacity = 1.0f;

    void mouseOver();
public:
    InputText(GLFWwindow* window, int windowWidth, int windowHeight);
    ~InputText();
    void render();
    void x(GLfloat xpos);
    void y(GLfloat ypos);
};


#endif //GAME_INPUTTEXT_H
