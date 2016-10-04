//
// Created by cod3r on 10/3/16.
//

#include "Mouse.h"

double Mouse::xpos;
double Mouse::ypos;

double Mouse::getXpos() {
    return xpos;
}

void Mouse::setXpos(double xpos) {
    Mouse::xpos = xpos;
}

double Mouse::getYpos() {
    return ypos;
}

void Mouse::setYpos(double ypos) {
    Mouse::ypos = ypos;
}
