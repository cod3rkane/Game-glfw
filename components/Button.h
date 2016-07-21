//
// Created by jlopes on 7/21/16.
//

#ifndef GAME_BUTTON_H
#define GAME_BUTTON_H


#include <GLFW/glfw3.h>

class Button {
    bool isActive;

    Button(GLFWwindow* window, int xpos, int ypos);
    ~Button();

private:
    double xpos;
    double ypos;
    GLFWwindow* window;
};


#endif //GAME_BUTTON_H
