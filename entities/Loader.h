//
// Created by Cod3r Kane on 10/22/2016
//

#ifndef GAME_LOADER_H
#define GAME_LOADER_H

#include "RawModel.h"
#include <GL/glew.h>
#include <vector>
#include <glm/vec3.hpp>

using namespace std;

class Loader {
private:
    vector<GLuint> VAOS;
    vector<GLuint> VBOS;
    vector<GLuint> textures;
    GLuint createVAO();
    void unbindVAO();
    void storeDataInAttributeList(GLuint attributeNumber, GLuint coordinateSize, const vector<glm::vec3> &positions);
    void bindIndicesBuffer(const vector<GLuint> &indices);
public:
    RawModel loadToVAO(const vector<glm::vec3> &positions, const vector<GLuint> &indices);
};

#endif
