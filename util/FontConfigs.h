//
// Created by cod3r on 21/08/2016.
//

#ifndef GAME_FONTCONFIGS_H
#define GAME_FONTCONFIGS_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include "Character.h"
#include <map>
#include "Shader.h"
#include <ext.hpp>

using namespace std;

class FontConfigs {
    /**
     * FreeType
     */
    FT_Library ft;
    /**
     * Font face
     */
    FT_Face face;
public:
    /**
     * Contains all characters
     */
    map<GLchar, Character> Characters;
    FontConfigs(FT_UInt fontSize);
    ~FontConfigs();
};


#endif //GAME_FONTCONFIGS_H
