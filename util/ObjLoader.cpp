//
// Created by Cod3r Kane on 10/17/2016
//

#include "ObjLoader.h"

void ObjLoader::loadObj(const GLchar* file) {
    // Read file in binary mode
    ifstream stallBin(file, ios::binary);

    const int Max = 80;
    char buff[Max];
    vector<string> tokens;
    string currLine;
    string delimiter = "/";
    size_t found;
    vector<glm::vec3> vertexVector;
    vector<int> vertexIndices;
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
            // cout << "its :v:" << endl;
            // cout << currLine << endl;
            v = glm::vec3(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
            vertexVector.push_back(v);
            // cout << v.x << " " << v.y << " " << v.z << endl;
        } else if (tokens[0] == "vt") {
            cout << "its :vt:" << endl;
        } else if (tokens[0] == "vn") {
            cout << "its :vn:" << endl;
        } else if (tokens[0] == "f") {
            cout << "its :f:" << endl;
            for (int i = 1; i < tokens.size(); i++) {
                cout << tokens[i] << endl;
                while (tokens[i].find(delimiter) != string::npos) {
                    found = tokens[i].find(delimiter);
                    tokens[i].replace(found, 1, " ");
                }

                istringstream str(tokens[i]);
                // split str in space
                for (string s2; str >> s2;) {
                    fs.push_back(s2);
                }
                cout << "normal string " << tokens[i] << endl;
                // for (int a = 0; a < fs.size(); a++) {
                //     // cout << "result: " << fs[a] << endl;
                //     // pegamos somente a posição 0 referente aos vertices por enquanto.
                //     vertexIndices.push_back(stoi(fs[0]));
                //     cout << "Added value: " << fs[0] << endl;
                // }
                cout << "Added value: " << fs[0] << endl;
                vertexIndices.push_back(stoi(fs[0]));
                fs.clear();
            }
        }

        tokens.clear();
    }

    // cout << "size of vertexIndices: " << vertexIndices.size() << endl;
    // cout << "size of vertexVector: " << vertexVector.size() << endl;

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

    cout << "size of vertexIndices: " << sizeof(vertices) << endl;
    cout << "size of vertexVector: " << sizeof(indices) << endl;
}

ObjLoader::~ObjLoader() {

}
