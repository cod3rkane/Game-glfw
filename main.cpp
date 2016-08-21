#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <tgmath.h>
#include "util/Shader.h"
#include "components/Rectangle.h"
#include <map>
#include "util/FontConfigs.h"

using namespace std;

const int WINDOW_W = 1280;
const int WINDOW_H = 720;

// Font Test
GLuint VAO, VBO;

void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, std::map<GLchar, Character> characters);

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

    // Setting Window pos Center in Monitor 1920 - 1080
    glfwSetWindowPos(window, 320, 180);

    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, keyCallBack);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "Failed to initialize Glew" << endl;
        return -1;
    }

    glViewport(0, 0, WINDOW_W, WINDOW_H);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader triangleShader("assets/Shaders/VertexShader.glsl", "assets/Shaders/FragmentShader.glsl");
    Shader EnemyShader("assets/Shaders/VertexShader.glsl", "assets/Shaders/FragmentShader.glsl");

    // ### Font
    Shader fontShader("assets/Shaders/FontVertexShader.glsl", "assets/Shaders/FontFragmentShader.glsl");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WINDOW_W), 0.0f, static_cast<GLfloat>(WINDOW_H));
    fontShader.use();
    glUniformMatrix4fv(glGetUniformLocation(fontShader.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    FontConfigs fontConfigs(18);

    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // #### End Font ####

    GLfloat blueColor[] = {0.38f, 0.44f, 1.0f};
    GLfloat redColor[] = {0.72f, 0.0f, 0.02f};

    Rectangle Enemy = Rectangle(redColor);
    Enemy.shader(&EnemyShader);
    Enemy.y(0.78f);

    Rectangle player = Rectangle(blueColor);
    player.shader(&triangleShader);
    player.y(-0.78f);
    // Player Texture
    int imageW, imageH;
    unsigned char *image = SOIL_load_image("assets/images/container.jpg", &imageW, &imageH, 0, SOIL_LOAD_RGB);
    player.textureImage(image, imageW, imageH);

    double xpos, ypos;

    while (!glfwWindowShouldClose(window)) {
        // Check and call events
        glfwPollEvents();

        // Game Logic here
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // Render Objects
        Enemy.render();
        player.render();

        RenderText(fontShader, "Project Melkor - Roch Studio", 5.0f, 5.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f), fontConfigs.Characters);
        RenderText(fontShader, "Cod3r Kane", 50.0f, 50.0f, 1.0f, glm::vec3(0.72f, 0.0f, 0.02f), fontConfigs.Characters);

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

void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, std::map<GLchar, Character> characters)
{
    // Activate corresponding render state
    shader.use();
    glUniform3f(glGetUniformLocation(shader.program, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = characters[*c];

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos,     ypos,       0.0, 1.0 },
                { xpos + w, ypos,       1.0, 1.0 },

                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                { xpos + w, ypos + h,   1.0, 0.0 }
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}