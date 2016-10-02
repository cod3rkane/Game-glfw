//
// Created by cod3r on 10/2/16.
//

#ifndef GAME_MATHS_H
#define GAME_MATHS_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

using namespace glm;

class Maths {
public:
    mat4 createTransformationMatrix(vec3 translation, float rx, float ry, float rz, float scale);
};


#endif //GAME_MATHS_H
