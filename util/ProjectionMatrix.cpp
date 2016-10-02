//
// Created by cod3r on 10/2/16.
//

#include "ProjectionMatrix.h"

ProjectionMatrix::ProjectionMatrix(float fov, GLfloat aspectRatio, float nearPlane, float farPlane) :
        fov(fov), aspectRatio(aspectRatio), nearPlane(nearPlane), farPlane(farPlane) {

}

float ProjectionMatrix::getFov() const {
    return fov;
}

void ProjectionMatrix::setFov(float fov) {
    ProjectionMatrix::fov = fov;
}

GLfloat ProjectionMatrix::getAspectRatio() const {
    return aspectRatio;
}

void ProjectionMatrix::setAspectRatio(GLfloat aspectRatio) {
    ProjectionMatrix::aspectRatio = aspectRatio;
}

float ProjectionMatrix::getNearPlane() const {
    return nearPlane;
}

void ProjectionMatrix::setNearPlane(float nearPlane) {
    ProjectionMatrix::nearPlane = nearPlane;
}

float ProjectionMatrix::getFarPlane() const {
    return farPlane;
}

void ProjectionMatrix::setFarPlane(float farPlane) {
    ProjectionMatrix::farPlane = farPlane;
}
