//
// Created by cod3r on 29/08/2016.
//

#ifndef GAME_SQUARE_H
#define GAME_SQUARE_H

#include "../util/Shader.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>

class Square {
    Shader* shaderPoint;
    GLuint VAO, VBO[2], EBO;
    GLfloat xPos = 0.0f, yPos = 0.0f, zPos = -1.0f;
    int windowWidth, windowHeight;
public:

    /**
     * Usados nos casos em que eu preciso declarar um Square para ser usado mais tarde. Ex em uma propertie of a class.
     * @return
     */
    Square() {}

    /**
     * this constructor setup the window, height and color of my object. Normaly use this constructor.
     * @param windowWidth
     * @param windowHeight
     * @param color
     * @return
     */
    Square(int windowWidth, int windowHeight, GLfloat color[]);

    /**
     * Destructor.
     */
    ~Square();

    /**
     * Draw the square object.
     */
    void render();

    /**
     * setup openGL configs. Basic generate the buffers for render.
     * @param color
     */
    void setupGL(GLfloat color[]);

    /**
     * set Shader propertie, used to set-up GLSL of my object.
     * @param shader
     */
    void shader(Shader* shader);

    /**
     * set x position.
     * @param x
     */
    void x(GLfloat x);

    /**
     * get x position.
     * @return GLfloat
     */
    GLfloat x();

    /**
     * set y position.
     * @param y
     */
    void y(GLfloat y);

    /**
     * get y position.
     * @return GLfloat
     */
    GLfloat y();

    /**
     * set z position.
     * @param z
     */
    void z(GLfloat z);

    /**
     * get z position.
     * @return GLfloat
     */
    GLfloat z();

    /**
     * set window width propertie, used in perspective projection.
     * @param width
     */
    void windowW(int width);

    /**
     * set window height, used in perspective projection.
     * @param heigth
     */
    void windowH(int height);
};


#endif //GAME_SQUARE_H
