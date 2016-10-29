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
#include <iterator>
#include <vector>
#include <unordered_map>

using namespace std;

class ObjLoader {
public:
    ObjLoader() {};
    ~ObjLoader();
    void loadObj(const GLchar* file);
};

#endif // GAME_OBJLOADER_H
