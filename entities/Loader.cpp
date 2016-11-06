//
// Created by Cod3r Kane on 10/22/2016
//

#include <iostream>
#include "Loader.h"

RawModel Loader::loadToVAO(const vector<glm::vec3> &positions, const vector<GLuint> &indices) {
    GLuint vaoID = this->createVAO();
    this->bindIndicesBuffer(indices);
    this->storeDataInAttributeList(0, 3, positions);
    this->storeDataInAttributeList(1, 3, positions);
    this->storeDataInAttributeList(2, 2, positions);
    this->unbindVAO();
    return RawModel(vaoID, (GLuint)indices.size());
}

RawModel Loader::loadToVAO(const vector<glm::vec3> &positions, const vector<GLuint> &indices,
                           const vector<glm::vec2> &textures, const vector<glm::vec3> &normals) {
    GLuint vaoID = this->createVAO();
    this->bindIndicesBuffer(indices);
    this->storeDataInAttributeList(0, 3, positions);
    this->storeDataInAttributeList(2, 2, textures);
    this->unbindVAO();
    return RawModel(vaoID, (GLuint)indices.size());
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

void Loader::storeDataInAttributeList(GLuint attributeNumber, GLuint coordinateSize, const vector<glm::vec3> &positions) {
    GLfloat vertices[positions.size()*3];

    int i = 0;
    for (int a = 0; a < positions.size(); a++) {
        vertices[i++] = positions[a].x;
        vertices[i++] = positions[a].y;
        vertices[i++] = positions[a].z;
    }

    GLuint vboID;
    glGenBuffers(1, &vboID);
    this->VBOS.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(attributeNumber);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, coordinateSize * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::storeDataInAttributeList(GLuint attributeNumber, GLuint coordinateSize, const vector<glm::vec2> &positions) {
    GLfloat vertices[positions.size()*2];
    int i = 0;
    for (int a = 0; a < positions.size(); a++) {
        vertices[i++] = positions[a].x;
        vertices[i++] = 1 - positions[a].y;
    }

    GLuint vboID;
    glGenBuffers(1, &vboID);
    this->VBOS.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(attributeNumber);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, coordinateSize * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::bindIndicesBuffer(const vector<GLuint> &indices) {
    GLuint ind[indices.size()];
    GLuint vboID;

    for (int i = 0; i < indices.size(); i++) {
        ind[i] = (indices[i] - 1);
    }

    glGenBuffers(1, &vboID);
    this->VBOS.push_back(vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);
}
