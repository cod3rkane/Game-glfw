//
// Created by Cod3r Kane on 29/10/2016
//

#include "ObjModel.h"

ObjModel::ObjModel(Shader &shader, const RawModel &rawModel) {
    this->shader = &shader;
    this->rawModel = &rawModel;
}

void ObjModel::render() {
    this->shader->use();

    mat4 transformationMatrix = this->maths.createTransformationMatrix(
            this->entity->getPosition(),
            this->entity->getRotX(),
            this->entity->getRotY(),
            this->entity->getRotZ(),
            this->entity->getScale()
    );

    mat4 projectionMatrix = glm::perspective(
            this->projectionMatrix->getFov(),
            this->projectionMatrix->getAspectRatio(),
            this->projectionMatrix->getNearPlane(),
            this->projectionMatrix->getFarPlane()
    );

    GLint transformationMatrixLocation = glGetUniformLocation(this->shader->program, "transform");
    GLint viewMatrixLocation = glGetUniformLocation(this->shader->program, "view");
    GLint projectionMatrixLocation = glGetUniformLocation(this->shader->program, "projection");

    glUniformMatrix4fv(transformationMatrixLocation, 1, GL_FALSE, glm::value_ptr(transformationMatrix));
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(*this->viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glBindVertexArray(this->rawModel->getVaoID());
    glDrawElements(GL_TRIANGLES, this->rawModel->getVertexCount() - 1, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void ObjModel::setEntity(const Entity &entity) {
    this->entity = &entity;
}

void ObjModel::setProjectionMatrix(const ProjectionMatrix &projectionMatrix) {
    this->projectionMatrix = &projectionMatrix;
}

void ObjModel::setViewMatrix(const mat4 &viewMatrix) {
    this->viewMatrix = &viewMatrix;
}

ObjModel::~ObjModel() {

}
