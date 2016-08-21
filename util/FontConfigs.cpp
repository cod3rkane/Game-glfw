//
// Created by cod3r on 21/08/2016.
//

#include "FontConfigs.h"

FontConfigs::FontConfigs(FT_UInt fontSize) {
    // Init FreeType Font
    if (FT_Init_FreeType(&this->ft)) {
        cout << "ERROR::FREETYPE: Could not init FreeType Library" << endl;
    }

    // Load FontFace
    if (FT_New_Face(this->ft, "assets/fonts/arial.ttf", 0, &this->face)) {
        cout << "ERROR::FREETYPE: Failed to load font" << endl;
    }

    // Set font size
    FT_Set_Pixel_Sizes(this->face, 0, fontSize);

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load first 128 characters of ASCII set
    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph
        if (FT_Load_Char(this->face, c, FT_LOAD_RENDER))
        {
            cout << "ERROR::FREETYTPE: Failed to load Glyph" << endl;
            continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                this->face->glyph->bitmap.width,
                this->face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                this->face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
                texture,
                glm::ivec2(this->face->glyph->bitmap.width, this->face->glyph->bitmap.rows),
                glm::ivec2(this->face->glyph->bitmap_left, this->face->glyph->bitmap_top),
                this->face->glyph->advance.x
        };
        this->Characters.insert(std::pair<GLchar, Character>(c, character));
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    // Destroy FreeType once we're finished
    FT_Done_Face(this->face);
    FT_Done_FreeType(this->ft);
}

FontConfigs::~FontConfigs() {

}