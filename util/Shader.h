//
// Created by jlopes on 7/21/16.
//

#ifndef GAME_SHADER_H
#define GAME_SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

using namespace std;

class Shader {
public:
    GLuint program = 0;

    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    ~Shader();
    void use();
};


#endif //GAME_SHADER_H
