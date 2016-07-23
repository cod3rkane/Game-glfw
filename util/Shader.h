//
// Created by jlopes on 7/21/16.
//

#ifndef GAME_SHADER_H
#define GAME_SHADER_H

#include <iostream>

using namespace std;

class Shader {
public:
    GLuint program;

    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    ~Shader();
    void use();
};


#endif //GAME_SHADER_H
