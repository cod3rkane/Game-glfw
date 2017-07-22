//
// Created by Cod3r Kane on 29/10/2016
//

#ifndef GAME_OBJMODEL_H
#define GAME_OBJMODEL_H

#include "../entities/RawModel.h"
#include "../entities/Entity.h"
#include "../util/Shader.h"
#include "../util/ProjectionMatrix.h"
#include "../util/Maths.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <SOIL.h>

using namespace glm;
using namespace std;

class ObjModel {
private:
    Shader *shader;
    const Entity *entity;
    const ProjectionMatrix *projectionMatrix;
    const mat4 *viewMatrix;
    Maths maths;
    const RawModel *rawModel;
    GLuint texture;
public:
    ObjModel(Shader &shader, const RawModel &rawModel);
    ~ObjModel();
    void render();
    void setEntity(const Entity &entity);
    void setProjectionMatrix(const ProjectionMatrix &projectionMatrix);
    void setViewMatrix(const mat4 &viewMatrix);
    void textureImage(unsigned char *image, int width, int height, GLenum format);
};

#endif
