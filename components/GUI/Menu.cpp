//
// Created by cod3r on 28/08/2016.
//

#include "Menu.h"

Menu::Menu(int windowWidth, int windowHeight) {
    GLfloat color[] = {0.955f, 0.477f, 0.099f};

    this->shader.setupGL("assets/Shaders/ModelViewProjectionTextured.vert", "assets/Shaders/ModelViewProjectionTextured.frag");
    int imageW, imageH;
    unsigned char *image = SOIL_load_image("assets/images/MenuTexture.png", &imageW, &imageH, 0, SOIL_LOAD_RGBA);

    this->square.windowW(windowWidth);
    this->square.windowH(windowHeight);
    this->square.shader(&this->shader);
    this->square.setupGL(color);
    this->square.textureImage(image, imageW, imageH, GL_RGBA);
    this->square.x(-0.5f);
    this->square.scale(0.4f);
}

void Menu::render() {
    this->square.render();
}

Menu::~Menu() {
    this->shader.~Shader();
}