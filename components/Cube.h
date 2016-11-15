//
// Created by cod3r on 18/09/2016.
//

#ifndef GAME_CUBE_H
#define GAME_CUBE_H

#include "../util/Shader.h"
#include "../entities/Entity.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include "../util/Maths.h"
#include "../util/ProjectionMatrix.h"

using namespace glm;

class Cube {
    Shader* ShaderPoint;
    Entity entity;
    ProjectionMatrix projectionMatrix;
    mat4 viewMatrix;
    GLuint VAO, VBO[3], EBO, myTexture = 0;
    int windowWidth, windowHeight;
    Maths maths;
public:
    Cube(int windowWidth, int windowHeight);
    Cube() {};
    void setupGL(int windowWidth, int windowHeight);
    void textureImage(unsigned char *image, int width, int height, GLenum format);
    void render();
    void shader(Shader* shader);

    const Entity &getEntity() const;

    void setEntity(const Entity &entity);

    const ProjectionMatrix &getProjectionMatrix() const;

    void setProjectionMatrix(const ProjectionMatrix &projectionMatrix);

    const mat4 &getViewMatrix() const;

    void setViewMatrix(const mat4 &viewMatrix);

    ~Cube();
};


#endif //GAME_CUBE_H
