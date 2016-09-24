//
// Created by cod3r on 21/08/2016.
//

#ifndef GAME_TEXTDRAW_H
#define GAME_TEXTDRAW_H


#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/ext.hpp>
#include "../util/Shader.h"
#include "../util/Character.h"
#include <map>

using namespace std;

class TextDraw {
    GLuint VBO, VAO, EBO;
    /**
     * Fragment and Vertex object Shader
     */
    Shader* myShader;
    /**
     * Window Width and Window Height
     */
    int windowW, windowH;
    /**
     * Text used to draw
     */
    string Text;
    /**
     * Position X, Y and Scale
     */
    GLfloat X, Y, Scale;
    /**
     * Text Color
     */
    glm::vec3 Color;
    /**
     * All Characters used for render text
     */
    std::map<GLchar, Character> Characters;
public:
    TextDraw(Shader* shader, int windowWidth, int windowHeight);
    TextDraw();
    ~TextDraw();
    void setupGL();
    void shader(Shader* shader);
    Shader* shader();
    void text(string text);
    string text();
    void x(GLfloat x);
    GLfloat x();
    void y(GLfloat y);
    GLfloat y();
    void scale(GLfloat scale);
    GLfloat scale();
    void color(glm::vec3 color);
    glm::vec3 color();
    void characters(map<GLchar, Character> characters);
    map<GLchar, Character> characters();
    void windowWidth(int width);
    int windowWidth();
    void windowHeight(int height);
    int windowHeight();
    /**
     * Draw my text
     */
    void render();
};


#endif //GAME_TEXTDRAW_H
