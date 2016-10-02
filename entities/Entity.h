//
// Created by cod3r on 10/2/16.
//

#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H


#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace glm;

class Entity {
    GLuint model;
    vec3 position;
    float rotX, rotY, rotZ;
    float scale;

public:
    Entity(GLuint model, const vec3 &position, float rotX, float rotY, float rotZ, float scale);

    Entity() {};

    void increasePosition(float dx, float dy, float dz);

    void increaseRotation(float dx, float dy, float dz);

    GLuint getModel() const;

    void setModel(GLuint model);

    const vec3 &getPosition() const;

    void setPosition(const vec3 &position);

    float getRotX() const;

    void setRotX(float rotX);

    float getRotY() const;

    void setRotY(float rotY);

    float getRotZ() const;

    void setRotZ(float rotZ);

    float getScale() const;

    void setScale(float scale);
};


#endif //GAME_ENTITY_H
