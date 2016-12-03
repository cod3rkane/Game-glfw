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

    // Bind myTexture using myTexture units
    if (this->texture) {
        // Bind myTexture using myTexture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->texture);
        glUniform1i(glGetUniformLocation(this->shader->program, "ourTexture"), 0);
    }

    GLint transformationMatrixLocation = glGetUniformLocation(this->shader->program, "transform");
    GLint viewMatrixLocation = glGetUniformLocation(this->shader->program, "view");
    GLint projectionMatrixLocation = glGetUniformLocation(this->shader->program, "projection");

    glUniformMatrix4fv(transformationMatrixLocation, 1, GL_FALSE, glm::value_ptr(transformationMatrix));
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(*this->viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glBindVertexArray(this->rawModel->getVaoID());
    glEnable(GL_DEPTH_TEST); // Essa linha evita com que o elemento fique transparente.
    glDrawElements(GL_TRIANGLES, this->rawModel->getVertexCount() - 1, GL_UNSIGNED_INT, 0);
    glDisable(GL_DEPTH_TEST);
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

void ObjModel::textureImage(unsigned char *image, int width, int height, GLenum format) {
    // @todo test if image has valid.
    try {
        // Load and create myTexture
        glGenTextures(1, &this->texture);
        glBindTexture(GL_TEXTURE_2D, this->texture);
        // Set out myTexture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        // Set myTexture filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        // Free memory image
        SOIL_free_image_data(image);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    } catch (unsigned char *image) {
        cout << "couldn't load image because: " << image << endl;
        throw "Error";
    } catch (int num) {
        cout << "couldn't load image because: " << num << endl;
        throw "Error";
    }
}

ObjModel::~ObjModel() {

}
