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
    string currLine;
    string delimiter = "/";
    size_t found;
    vector<glm::vec3> vertexVector;
    vector<GLuint> vertexIndices;
    vector<string> fs;
    glm::vec3 v;

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
            cout << "its :vt:" << endl;
        } else if (tokens[0] == "vn") {
            cout << "its :vn:" << endl;
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
                fs.clear();
            }
        }

        tokens.clear();
    }

    // vezes 3 porque temos x,y e z
    GLfloat vertices[vertexVector.size()*3];
    GLuint indices[vertexIndices.size()];

    int i = 0;
    for (int a = 0; a < vertexVector.size(); a++) {
        vertices[i++] = vertexVector[a].x;
        vertices[i++] = vertexVector[a].y;
        vertices[i++] = vertexVector[a].z;
    }

    for (int i = 0; i < vertexIndices.size(); i++) {
        indices[i] = (vertexIndices[i] - 1);
    }

    return loader.loadToVAO(vertexVector, vertexIndices);
}

ObjLoader::~ObjLoader() {

}
