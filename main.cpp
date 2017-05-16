#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "util/Shader.h"
#include <map>
#include "util/FontConfigs.h"
#include "components/TextDraw.h"
#include "components/InputText.h"
#include "components/Cube.h"
#include "components/ObjModel.h"
#include "util/Camera.h"
#include "util/ObjLoader.h"
#include "entities/RawModel.h"

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

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    Mouse::setXpos(xpos);
    Mouse::setYpos(ypos);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to left

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

int main(int argc, char** argv) {
    // @todo used for alter monitor or NULL when we're create window.
    string isDebug = (argc > 1 ? argv[1] : "");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    monitor = glfwGetPrimaryMonitor();
    mode = glfwGetVideoMode(monitor);

    window = glfwCreateWindow(mode->width, mode->height, "Project Melkor - Roch Studio", NULL, NULL);
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
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwMakeContextCurrent(window);

    // @todo remove this line
    if (isDebug != "debug") {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "Failed to initialize Glew" << endl;
        return -1;
    }

    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, mode->width, mode->height);
    glMatrixMode(GL_MODELVIEW);

    Shader modelViewProjectionTextured(
            "F:\\Game-glfw\\assets\\Shaders\\ModelViewProjectionTextured.vert",
            "F:\\Game-glfw\\assets\\Shaders\\ModelViewProjectionTextured.frag"
    );

    Shader modelViewProjectionColor(
            "F:\\Game-glfw\\assets\\Shaders\\ModelViewProjection.vert",
            "F:\\Game-glfw\\assets\\Shaders\\ModelViewProjection.frag"
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
        dirtTexture = SOIL_load_image((i >= 30 ? "F:\\Game-glfw\\assets\\images\\stone.jpg" : "F:\\Game-glfw\\assets\\images\\dirt.jpg"), &imageW, &imageH, 0, SOIL_LOAD_RGB);
        cubes[i]->textureImage(dirtTexture, imageW, imageH, GL_RGB);
    }

    // ### Font Configs
    Shader fontShader("F:\\Game-glfw\\assets\\Shaders\\FontVertexShader.glsl", "F:\\Game-glfw\\assets\\Shaders\\FontFragmentShader.glsl");
    FontConfigs fontConfigs(18);
    // ### End Font Configs

    TextDraw playerText(&fontShader, mode->width, mode->height);
    playerText.characters(fontConfigs.Characters);
    playerText.color(glm::vec3(0.5, 0.8f, 0.2f));

    Loader loader;
    ObjLoader stallObj = ObjLoader();
    RawModel firstRawModel = stallObj.loadObj("F:\\Game-glfw\\assets\\Models\\stall.obj", loader);
    ObjModel stallModel(modelViewProjectionTextured, firstRawModel);
    unsigned char *stallTexture = SOIL_load_image("F:\\Game-glfw\\assets\\images\\stallTexture.png", &imageW, &imageH, 0, SOIL_LOAD_RGB);
    stallModel.textureImage(stallTexture, imageW, imageH, GL_RGB);
    Entity test(0, vec3(0, 0, 0), 0, 0, 0, 1);
    stallModel.setEntity(test);

    while (!glfwWindowShouldClose(window)) {
        // Check and call events
        glfwPollEvents();

        // Game Logic here
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0f);

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

        for (int i = 0; i < 50; i++) {
            cubes[i]->setViewMatrix(camera.GetViewMatrix());
            cubes[i]->setProjectionMatrix(projectionMatrix);
            cubes[i]->render();
        }

        stallModel.setViewMatrix(camera.GetViewMatrix());
        stallModel.setProjectionMatrix(projectionMatrix);
        stallModel.render();

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
void Do_Movement() {
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
