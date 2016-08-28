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
#include "TextDraw.h"
#include <map>
#include "../util/Character.h"

using namespace std;

class InputText {
    string inputText;
    static string convertCharToString;
    static double mouseXpos, mouseYPos;
    static int windowW, windowH;
    GLuint VBO[2], VAO, EBO;
    Shader shader = Shader("assets/Shaders/Color-Position-Projection.vert", "assets/Shaders/Color-Position-Projection.frag");
    Shader* FontShader;
    GLfloat xPos = 0.0f;
    GLfloat yPos = 0.0f;
    GLfloat xScale = 0.3f;
    GLfloat yScale = 0.04f;
    GLfloat opacity = 1.0f;
    bool isActive = false;
    bool isMouseOver = false;
    TextDraw textDraw = TextDraw();
    int MouseButton, MouseAction, keyboardKey;
    unsigned int codepoint;
    int characterLimiter = 30;

    // Esses métodos estaticos precisam sumir logo, o ideal é termos um unico GLFWsetMousePositionCallback e e GLFWSetMouseButtonCallback
    // Mas para fazermos isso precisamos terminar nossa Classe de Window(GameWindow) e GameLoop.
    // @todo remove cursorPositionCallBack and mouseButtonCallback when Window and GameLoop Class done.
    static void cursorPositionCallBack(GLFWwindow* window, double xpos, double ypos);
    void mouseOver();
    void mouseClick();
    void setUpTextDraw();
    void renderTextDraw();
public:
    InputText(GLFWwindow* window, int windowWidth, int windowHeight);
    ~InputText();
    void render();
    void x(GLfloat xpos);
    void y(GLfloat ypos);
    void fontShader(Shader* shader);
    void characters(map<GLchar, Character> characters);
    void text(string text);
    string text();
    void receiveKeyboardEvents();
    void mouseButton(int button);
    void mouseAction(int action);
    void keyboardKeyCode(int key);
    void codePoint(unsigned int code);
    void setupInputs(int button, int action, int key, unsigned int code);
    void maxCharacter(int max);
    int maxCharacter();
};


#endif //GAME_INPUTTEXT_H
