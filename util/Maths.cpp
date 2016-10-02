//
// Created by cod3r on 10/2/16.
//

#include "Maths.h"

mat4 Maths::createTransformationMatrix(vec3 translation, float rx, float ry, float rz, float scale) {
    mat4 matrix;
    matrix = translate(matrix, translation);
    matrix = rotate(matrix, radians(rx), vec3(1.0f, 0.0f, 0.0f));
    matrix = rotate(matrix, radians(ry), vec3(0.0f, 1.0f, 0.0f));
    matrix = rotate(matrix, radians(rz), vec3(0.0f, 0.0f, 1.0f));
    matrix = glm::scale(matrix, vec3(scale, scale, scale));
    return matrix;
}
