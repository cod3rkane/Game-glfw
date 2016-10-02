//
// Created by cod3r on 10/2/16.
//

#ifndef GAME_PROJECTIONMATRIX_H
#define GAME_PROJECTIONMATRIX_H


#include <GL/glew.h>

class ProjectionMatrix {
    float fov = 45.0f;
    GLfloat aspectRatio;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

public:
    ProjectionMatrix(float fov, GLfloat aspectRatio, float nearPlane, float farPlane);
    ProjectionMatrix() {};

    float getFov() const;

    void setFov(float fov);

    GLfloat getAspectRatio() const;

    void setAspectRatio(GLfloat aspectRatio);

    float getNearPlane() const;

    void setNearPlane(float nearPlane);

    float getFarPlane() const;

    void setFarPlane(float farPlane);
};


#endif //GAME_PROJECTIONMATRIX_H
