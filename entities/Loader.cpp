//
// Created by Cod3r Kane on 10/22/2016
//

#include "Loader.h"

RawModel Loader::loadToVAO(GLfloat positions[], GLuint indices[]) {
    GLuint vaoID = this->createVAO();
    this->bindIndicesBuffer(indices);
    this->storeDataInAttributeList(0, 3, positions);
    this->unbindVAO();
    return RawModel(vaoID, sizeof(indices));
}

GLuint Loader::createVAO() {
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    this->VAOS.push_back(vaoID);
    glBindVertexArray(vaoID);
    return vaoID;
}

void Loader::unbindVAO() {
    glBindVertexArray(0);
}

void Loader::storeDataInAttributeList(GLuint attributeNumber, GLuint coordinateSize, GLfloat data[]) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    this->VBOS.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(attributeNumber);
    glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::bindIndicesBuffer(GLuint indices[]) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    this->VBOS.push_back(vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}
