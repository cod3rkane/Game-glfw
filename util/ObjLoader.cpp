//
// Created by Cod3r Kane on 10/17/2016
//

#include <iterator>
#include <vector>
#include <unordered_map>
#include "ObjLoader.h"

void ObjLoader::loadObj(const GLchar* objFile) {
    string objCode;
    ifstream objFileStream;
    objFileStream.exceptions(ifstream::badbit);
    stringstream stream;

    try {
        objFileStream.open(objFile);
        stream << objFileStream.rdbuf();
        objFileStream.close();
        objCode = stream.str();
    } catch (ifstream::failure e) {
        cout << "ERROR::OBJLOADER::FILE_NOT_SUCCESFULLY_READ" << endl;
    }

    cout << objCode.c_str() << endl;

    const int maxBuffer = 80;
    char lineChar[maxBuffer];
    string line;
    vector<glm::vec3> vertices;
    vector<glm::vec2> textures;
    vector<glm::vec3> normals;
    vector<int> indices;

    // @todo fazer um loop infinito para ler cada linha do .obj e pegar os v, vt, vn e f
    while (!stream.eof()) {
        vector<string> tokens;
        stream.getline(lineChar, maxBuffer);
        line = lineChar;

        if (line != "") {
            istringstream iss(line);
            copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));

            if (tokens[0] == "v") {
                // Get vertices
                // @todo se der algum erro de posições muito loucas, pode ser aqui, não está convertendo exatamente igual.
                glm::vec3 v(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
                vertices.push_back(v);
            } else if (tokens[0] == "vt") {
                // Get textures
                glm::vec2 vt(stof(tokens[1]), stof(tokens[2]));
                textures.push_back(vt);
            } else if (tokens[0] == "vn") {
                glm::vec3 vn(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
                normals.push_back(vn);
            }
        }
    }

    stream.clear();
    stream.str(objCode);

    while (!stream.eof()) {
        vector<string> tokens;
        stream.getline(lineChar, maxBuffer);
        line = lineChar;

        if (line != "") {
            istringstream iss(line);
            copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));

            if (tokens[0] != "f") {
                continue;
            }

            string delimiter = "/";
            indices.push_back(stoi(tokens[1].substr(0, tokens[1].find(delimiter))));
            indices.push_back(stoi(tokens[2].substr(0, tokens[1].find(delimiter))));
            indices.push_back(stoi(tokens[3].substr(0, tokens[1].find(delimiter))));
        }
    }

    float vertexArray[vertices.size()*3];
    int indicesArray[indices.size()];

    int vertexPointer = 0, i = 0;
    for (vertexPointer; vertexPointer < vertices.size();) {
        vertexArray[vertexPointer++] = vertices[i].x;
        vertexArray[vertexPointer++] = vertices[i].y;
        vertexArray[vertexPointer++] = vertices[i].z;
    }

    for (i = 0; i < indices.size(); i++) {
        indicesArray[i] = (indices[i]) - 1;
    }
}

ObjLoader::~ObjLoader() {

}