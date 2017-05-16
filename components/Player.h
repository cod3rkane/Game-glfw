//
// Created by cod3r on 10/1/16.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "../util/Shader.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include "../util/Camera.h"

class Player {
    Shader* ShaderPoint;
    GLuint VAO, VBO[2], EBO, TextureID = 0;
    GLfloat xPos = 0.0f, yPos = 0.0f, zPos = -1.0f, Scale = 0.17f;
    int windowWidth, windowHeight;
    Camera camera;
public:
    Player(int windowWidth, int windowHeight);
    Player() {};
    ~Player();
    void setupGL();
    void render();

    /*** Getter and Setters ***/
    Shader *getShaderPoint() const;
    void setShaderPoint(Shader *ShaderPoint);
    GLfloat getXPos() const;
    void setXPos(GLfloat xPos);
    GLfloat getYPos() const;
    void setYPos(GLfloat yPos);
    GLfloat getZPos() const;
    void setZPos(GLfloat zPos);
    GLfloat getScale() const;
    void setScale(GLfloat Scale);
    int getWindowWidth() const;
    void setWindowWidth(int windowWidth);
    int getWindowHeight() const;
    void setWindowHeight(int windowHeight);
    const Camera &getCamera() const;
    void setCamera(const Camera &camera);
};


#endif //GAME_PLAYER_H
