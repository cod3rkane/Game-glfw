//
// Created by Cod3r Kane on 10/17/2016
//

#include "ObjLoader.h"

RawModel ObjLoader::loadObj(const GLchar* file, Loader &loader) {
    // Read file in binary mode
    ifstream stallBin(file, ios::binary);

    const int Max = 80;
    char buff[Max];
    vector<string> tokens;
    string currLine, delimiter = "/";
    size_t found;
    vector<glm::vec3> vertexVector, vertexNormals;
    vector<glm::vec2> vertexTexture, vertexTextureNormalized;
    vector<GLuint> vertexIndices, vertexFTextures;
    vector<string> fs;
    glm::vec3 v, vn;
    glm::vec2 vt;

    while (!stallBin.eof()) {
        stallBin.getline(buff, Max);
        currLine = buff;

        istringstream strToSplit(currLine);
        // split str in space
        for (string s; strToSplit >> s;) {
            tokens.push_back(s);
        }

        if (tokens[0] == "v") {
            v = glm::vec3(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
            vertexVector.push_back(v);
        } else if (tokens[0] == "vt") {
            vt = glm::vec2(stof(tokens[1]), stof(tokens[2]));
            vertexTexture.push_back(vt);
        } else if (tokens[0] == "vn") {
            vn = glm::vec3(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
            vertexNormals.push_back(vn);
        } else if (tokens[0] == "f") {
            for (int i = 1; i < tokens.size(); i++) {
                while (tokens[i].find(delimiter) != string::npos) {
                    found = tokens[i].find(delimiter);
                    tokens[i].replace(found, 1, " ");
                }

                istringstream str(tokens[i]);
                // split str in space
                for (string s2; str >> s2;) {
                    fs.push_back(s2);
                }

                vertexIndices.push_back(stoi(fs[0]));
                vertexFTextures.push_back(stoi(fs[1]));
                fs.clear();
            }
        }

        tokens.clear();
    }

    return loader.loadToVAO(vertexVector, vertexIndices, vertexTexture, vertexNormals);
}

ObjLoader::~ObjLoader() {

}
