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
#include "../entities/Loader.h"
#include "../entities/RawModel.h"

using namespace std;

class ObjLoader {
public:
    ObjLoader() {};
    ~ObjLoader();
    RawModel loadObj(const GLchar* file, Loader &loader);
};

#endif // GAME_OBJLOADER_H
