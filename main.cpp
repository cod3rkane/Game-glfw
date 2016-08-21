#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <tgmath.h>
#include "util/Shader.h"
#include "components/Rectangle.h"

using namespace std;

const int WINDOW_W = 1280;
const int WINDOW_H = 720;

static void error_callback(int error, const char* desc) {
    cout << "Error: " << desc << endl;
}

static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_W, WINDOW_H, "Project Melkor - Roch Studio", NULL, NULL);
    if (!window) {
        cout << "could not create Window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, keyCallBack);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "Failed to initialize Glew" << endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glViewport(0, 0, WINDOW_W, WINDOW_H);

    Shader triangleShader("assets/Shaders/VertexShader.glsl", "assets/Shaders/FragmentShader.glsl");

    GLfloat blueColor[] = {0.38f, 0.44f, 1.0f};
    GLfloat redColor[] = {0.72f, 0.0f, 0.02f};

    Rectangle player = Rectangle(blueColor);
    Rectangle Enemy = Rectangle(redColor);

    player.shader(&triangleShader);
//    player.x(0.6f);
    player.y(-0.78f);

    Enemy.shader(&triangleShader);
//    Enemy.x(0.f);
    Enemy.y(0.78f);

    double xpos, ypos;

    while (!glfwWindowShouldClose(window)) {
        // Check and call events
        glfwPollEvents();

        // Game Logic here
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // Render Objects
        player.render();
        Enemy.render();

        // mouse pos
//        glfwGetCursorPos(window, &xpos, &ypos);
//        cout << "Xpos:" << xpos << endl;
//        cout << "Ypos:" << ypos << endl;

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}