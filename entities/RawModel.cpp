#include "RawModel.h"

RawModel::RawModel(int VaoID, int VertexCount) : VaoID(VaoID), VertexCount(VertexCount) {}

int RawModel::getVaoID() const {
    return VaoID;
}

void RawModel::setVaoID(int VaoID) {
    RawModel::VaoID = VaoID;
}

int RawModel::getVertexCount() const {
    return VertexCount;
}

void RawModel::setVertexCount(int VertexCount) {
    RawModel::VertexCount = VertexCount;
}
