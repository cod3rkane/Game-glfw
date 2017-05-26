//
// Created by cod3r on 28/08/2016.
//

#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "../Square.h"
#include <SOIL/SOIL.h>

class Menu {
    Shader shader;
    Square square = Square();
public:
    Menu(int windowWidth, int windowHeight);
    void render();
    ~Menu();
};


#endif //GAME_MENU_H
