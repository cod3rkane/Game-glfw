//
//  Created by Cod3r Kane on 10/17/2016
//

#ifndef GAME_OBJLOADER_H
#define GAME_OBJLOADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <GL/glew.h>
#include <glm/ext.hpp>

using namespace std;

class ObjLoader {
public:
    ObjLoader() {};
    ~ObjLoader();
    void loadObj(const GLchar* objFile);
};

#endif // GAME_OBJLOADER_H