//
// Created by Cod3r Kane on 10/22/2016
//

#ifndef GAME_LOADER_H
#define GAME_LOADER_H

#include "RawModel.h"
#include <GL/glew.h>
#include <vector>

using namespace std;

class Loader {
private:
    vector<GLuint> VAOS;
    vector<GLuint> VBOS;
    vector<GLuint> textures;
    GLuint createVAO();
    void unbindVAO();
    void storeDataInAttributeList(GLuint attributeNumber, GLuint coordinateSize, GLfloat data[]);
    void bindIndicesBuffer(GLuint indices[]);
public:
    RawModel loadToVAO(GLfloat positions[], GLuint indices[]);
};

#endif
