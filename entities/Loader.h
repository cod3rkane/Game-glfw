//
// Created by Cod3r Kane on 10/22/2016
//

#ifndef GAME_LOADER_H
#define GAME_LOADER_H

#include "RawModel.h"

class Loader {
private:
    int createVAO();
public:
    RawModel loadToVAO();
};

#endif
