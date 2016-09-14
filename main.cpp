#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "util/Shader.h"
#include "components/Rectangle.h"
#include <map>
#include "util/FontConfigs.h"
#include "components/TextDraw.h"
#include "components/InputText.h"
#include "components/Square.h"
#include "components/GUI/Menu.h"

using namespace std;

// default window size
int WINDOW_W = 1280;
int WINDOW_H = 720;

GLFWwindow *window;
GLFWmonitor* monitor;
const GLFWvidmode* mode;

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

        if (key == GLFW_KEY_F11) {
            // Set full screen window
            glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
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

    monitor = glfwGetPrimaryMonitor();
    mode = glfwGetVideoMode(monitor);

    window = glfwCreateWindow(mode->width, mode->height, "Project Melkor - Roch Studio", monitor, NULL);
    if (!window) {
        cout << "could not create Window" << endl;
        glfwTerminate();
        return -1;
    }

    // Setting Window pos Center in Monitor 1920 - 1080
//    glfwSetWindowPos(window, 320, 180);

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
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, mode->width, mode->height);
    glMatrixMode(GL_MODELVIEW);


    Shader triangleShader("assets/Shaders/VertexShader.glsl", "assets/Shaders/FragmentShader.glsl");
    Shader modelViewProjection("assets/Shaders/ModelViewProjection.vert", "assets/Shaders/ModelViewProjection.frag");

    GLfloat purpleColor[] = {0.09f, 0.95f, 0.14f};
    GLfloat blueColor[] = {0.38f, 0.44f, 1.0f};
    GLfloat redColor[] = {0.72f, 0.0f, 0.02f};

    Menu menuGUI(mode->width, mode->height);

    Square mySquare(mode->width, mode->height, purpleColor);
    mySquare.shader(&modelViewProjection);

    Square mySquare2(mode->width, mode->height, redColor);
    mySquare2.shader(&modelViewProjection);

    // ### Font Configs
    Shader fontShader("assets/Shaders/FontVertexShader.glsl", "assets/Shaders/FontFragmentShader.glsl");
    FontConfigs fontConfigs(18);
    // ### End Font Configs

    InputText inputText(window, mode->width, mode->height);
//    inputText.maxCharacter(45);
    inputText.scaleX(0.2);
    inputText.scaleY(0.03);
    inputText.fontShader(&fontShader);
    inputText.characters(fontConfigs.Characters);
    inputText.setUpPosition();

    InputText input2(window, mode->width, mode->height);
    input2.fontShader(&fontShader);
    input2.characters(fontConfigs.Characters);
    input2.text("My Default Text");
    input2.setUpPosition();

    TextDraw playerText(&fontShader, mode->width, mode->height);
    playerText.characters(fontConfigs.Characters);
    playerText.color(glm::vec3(0.5, 0.8f, 0.2f));

//    Rectangle Enemy = Rectangle(redColor);
//    Enemy.shader(&triangleShader);
//    Enemy.x(0.2f);
//    Enemy.z(0.2f);

    Rectangle player = Rectangle(blueColor);
    player.shader(&triangleShader);
    player.z(0.0f);
    // Player Texture
    int imageW, imageH;
    unsigned char *image = SOIL_load_image("assets/images/container.jpg", &imageW, &imageH, 0, SOIL_LOAD_RGB);
    player.textureImage(image, imageW, imageH);

    while (!glfwWindowShouldClose(window)) {
        // Check and call events
        glfwPollEvents();

        // Game Logic here
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // Render Objects
//        Enemy.render();
//        player.render();

        // Render Text
        playerText.x(1.0f);
        playerText.y(1.0f);
        playerText.scale(1.0f);
        playerText.text("Created By Cod3r Kane");
        playerText.render();

        inputText.setupInputs(mouseButton, mouseAction, keyboardkey, charCodePoint);
        inputText.x(-0.78f);
        inputText.render();
        inputText.receiveKeyboardEvents();

        input2.setupInputs(mouseButton, mouseAction, keyboardkey, charCodePoint);
        input2.x(0.78f);
        input2.receiveKeyboardEvents();
        input2.render();

        mySquare.x(0.4f);
        mySquare.render();

        mySquare2.x(0.7f);
        mySquare2.z(-0.999f);
        mySquare2.render();

        menuGUI.render();

        glfwSwapBuffers(window);

        // clean inputs
        keyboardkey = 0;
        charCodePoint = 0;
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}