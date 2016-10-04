//
// Created by cod3r on 10/3/16.
//

#ifndef GAME_MOUSE_H
#define GAME_MOUSE_H


class Mouse {
    static double xpos;
    static double ypos;
public:
    static double getXpos();

    static void setXpos(double xpos);

    static double getYpos();

    static void setYpos(double ypos);
};


#endif //GAME_MOUSE_H
