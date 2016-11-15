//
// Created by cod3r on 21/08/2016.
//

#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    signed long Advance;    // Horizontal offset to advance to next glyph
};

#endif //GAME_CHARACTER_H