#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "util/Shader.h"
#include <map>
#include "util/FontConfigs.h"
#include "components/TextDraw.h"
#include "components/InputText.h"
#include "components/Cube.h"
#include "util/ProjectionMatrix.h"
#include "util/Camera.h"

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

// Camera Configs
void Do_Movement();

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

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

        if (key >= 0 && key < 1024) {
            keys[key] = true;
        }
    } else if (action == GLFW_RELEASE) {
        keyboardkey = 0;
        keys[key] = false;
    }
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    mouseButton = button;
    mouseAction = action;
}

void character_callback(GLFWwindow* window, unsigned int codepoint, int mods) {
    charCodePoint = codepoint;
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

    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, mode->width, mode->height);
    glMatrixMode(GL_MODELVIEW);

    Shader modelViewProjectionTextured(
            "assets/Shaders/ModelViewProjectionTextured.vert",
            "assets/Shaders/ModelViewProjectionTextured.frag"
    );

    ProjectionMatrix projectionMatrix;
    projectionMatrix.setAspectRatio((GLfloat)mode->width / mode->height);

    int imageW, imageH;
    unsigned char *dirtTexture;

    Entity *entity[50];
    Cube *cubes[50];

    for (int i = 0; i < 50; i++) {
//        int num = (i >= 10 ? (i / 10) : 0);
//        entity[i] = new Entity(0, vec3((i * 1), -2, (num * -1)), 0, 0, 0, 1);
//
        if (i < 10)
            entity[i] = new Entity(0, vec3(i * 1, -2, 0), 0, 0, 0, 1);
        else if (i >= 10 && i < 20)
            entity[i] = new Entity(0, vec3((i - 10) * 1, -2, -1), 0, 0, 0, 1);
        else if (i >= 20 && i < 30)
            entity[i] = new Entity(0, vec3((i - 20) * 1, -2, -2), 0, 0, 0, 1);
        else if (i >= 30 && i < 40)
            entity[i] = new Entity(0, vec3((i - 30) * 1, -2, -3), 0, 0, 0, 1);
        else if (i >= 40 && i < 50)
            entity[i] = new Entity(0, vec3((i - 40) * 1, -2, -4), 0, 0, 0, 1);

        cubes[i] = new Cube(mode->width, mode->height);

        cubes[i]->setEntity(*entity[i]);
        cubes[i]->shader(&modelViewProjectionTextured);
        dirtTexture = SOIL_load_image((i >= 30 ? "assets/images/stone.jpg" : "assets/images/dirt.jpg"), &imageW, &imageH, 0, SOIL_LOAD_RGB);
        cubes[i]->textureImage(dirtTexture, imageW, imageH, GL_RGB);
    }

    // ### Font Configs
    Shader fontShader("assets/Shaders/FontVertexShader.glsl", "assets/Shaders/FontFragmentShader.glsl");
    FontConfigs fontConfigs(18);
    // ### End Font Configs
    InputText inputText(window, mode->width, mode->height);
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

    while (!glfwWindowShouldClose(window)) {
        // Check and call events
        glfwPollEvents();

        // Game Logic here
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.400f, 0.750f, 1.00f, 1.0f);

        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        Do_Movement();

        // Render Text
        playerText.x(1.0f);
        playerText.y(1.0f);
        playerText.scale(1.0f);
        playerText.text("Created By Cod3r Kane");
        playerText.render();

        inputText.setupInputs(mouseButton, mouseAction, keyboardkey, charCodePoint);
        inputText.x(-0.78f);
        inputText.y(0.78f);
        inputText.render();
        inputText.receiveKeyboardEvents();

        input2.setupInputs(mouseButton, mouseAction, keyboardkey, charCodePoint);
        input2.y(0.78f);
        input2.x(0.78f);
        input2.receiveKeyboardEvents();
        input2.render();

        for (int i = 0; i < 50; i++) {
            cubes[i]->setViewMatrix(camera.GetViewMatrix());
            cubes[i]->setProjectionMatrix(projectionMatrix);
            cubes[i]->render();
        }

        glfwSwapBuffers(window);

        // clean inputs
        keyboardkey = 0;
        charCodePoint = 0;
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

// Moves/alters the camera positions based on user input
void Do_Movement()
{
    // Camera controls
    if(keys[GLFW_KEY_W])
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if(keys[GLFW_KEY_S])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if(keys[GLFW_KEY_A])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if(keys[GLFW_KEY_D])
        camera.ProcessKeyboard(RIGHT, deltaTime);
}