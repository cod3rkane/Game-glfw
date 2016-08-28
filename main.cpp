#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "util/Shader.h"
#include "components/Rectangle.h"
#include <map>
#include "util/FontConfigs.h"
#include "components/TextDraw.h"
#include "components/InputText.h"

using namespace std;

const int WINDOW_W = 1280;
const int WINDOW_H = 720;

// @todo remove these variables when GameLoop and GameWindow done.
int keyboardkey, mouseButton, mouseAction;
unsigned int charCodePoint;

static void error_callback(int error, const char *desc) {
    cout << "Error: " << desc << endl;
}

static void keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        keyboardkey = key;
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    } else if (action == GLFW_RELEASE) {
        keyboardkey = 0;
    }

}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    mouseButton = button;
    mouseAction = action;
}

void character_callback(GLFWwindow* window, unsigned int codepoint, int mods) {
    charCodePoint = codepoint;
//    cout << static_cast<unsigned char>(static_cast<unsigned int>(codepoint)) << endl;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(WINDOW_W, WINDOW_H, "Project Melkor - Roch Studio", NULL, NULL);
    if (!window) {
        cout << "could not create Window" << endl;
        glfwTerminate();
        return -1;
    }

    // Setting Window pos Center in Monitor 1920 - 1080
    glfwSetWindowPos(window, 320, 180);

    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, keyCallBack);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCharModsCallback(window, character_callback);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "Failed to initialize Glew" << endl;
        return -1;
    }

    glEnable(GL_DEPTH);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, WINDOW_W, WINDOW_H);
    glMatrixMode(GL_MODELVIEW);


    Shader triangleShader("assets/Shaders/VertexShader.glsl", "assets/Shaders/FragmentShader.glsl");

    // ### Font Configs
    Shader fontShader("assets/Shaders/FontVertexShader.glsl", "assets/Shaders/FontFragmentShader.glsl");
    FontConfigs fontConfigs(18);
    // ### End Font Configs

    InputText inputText(window, WINDOW_W, WINDOW_H);
    inputText.fontShader(&fontShader);
    inputText.characters(fontConfigs.Characters);

    InputText input2(window, WINDOW_W, WINDOW_H);
    input2.fontShader(&fontShader);
    input2.characters(fontConfigs.Characters);
    input2.text("My Default Text");

    TextDraw playerText(&fontShader, WINDOW_W, WINDOW_H);
    playerText.characters(fontConfigs.Characters);
    playerText.color(glm::vec3(0.5, 0.8f, 0.2f));

    GLfloat blueColor[] = {0.38f, 0.44f, 1.0f};
    GLfloat redColor[] = {0.72f, 0.0f, 0.02f};

    Rectangle Enemy = Rectangle(redColor);
    Enemy.shader(&triangleShader);
    Enemy.y(0.78f);

    Rectangle player = Rectangle(blueColor);
    player.shader(&triangleShader);
    player.y(-0.78f);
    // Player Texture
    int imageW, imageH;
    unsigned char *image = SOIL_load_image("assets/images/container.jpg", &imageW, &imageH, 0, SOIL_LOAD_RGB);
    player.textureImage(image, imageW, imageH);

    while (!glfwWindowShouldClose(window)) {
        // Check and call events
        glfwPollEvents();

        // Game Logic here
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // Render Objects
        Enemy.render();
        player.render();

        // Render Text
        playerText.x(1.0f);
        playerText.y(1.0f);
        playerText.scale(1.0f);
        playerText.text("Created By Cod3r Kane");
        playerText.render();

        inputText.setupInputs(mouseButton, mouseAction, keyboardkey, charCodePoint);
        inputText.x(-0.4f);
        inputText.render();
        inputText.receiveKeyboardEvents();

        input2.setupInputs(mouseButton, mouseAction, keyboardkey, charCodePoint);
        input2.x(0.3f);
        input2.receiveKeyboardEvents();
        input2.render();

        glfwSwapBuffers(window);
        // clean inputs
        keyboardkey = 0;
        charCodePoint = 0;
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}