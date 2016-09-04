//
// Created by cod3r on 28/08/2016.
//

#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "../../util/Shader.h"

class Menu {
    Shader* menuShader;
    GLfloat xPos = 0.0f, yPos = 0.0f, opacity = 1.0f;

public:
    Menu(Shader* shader);
    ~Menu();
};


#endif //GAME_MENU_H
