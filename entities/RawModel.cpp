#include "RawModel.h"

RawModel::RawModel(GLuint VaoID, GLuint VertexCount) : VaoID(VaoID), VertexCount(VertexCount) {}

GLuint RawModel::getVaoID() const {
    return VaoID;
}

void RawModel::setVaoID(GLuint VaoID) {
    RawModel::VaoID = VaoID;
}

GLuint RawModel::getVertexCount() const {
    return VertexCount;
}

void RawModel::setVertexCount(GLuint VertexCount) {
    RawModel::VertexCount = VertexCount;
}
