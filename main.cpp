#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

static void error_callback(int error, const char* desc) {
    cout << "Error: " << desc << endl;
}

static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Winters Survivor - Project - BuildDev", NULL, NULL);
    if (!window) {
        cout << "could not create Window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    // Triangle
    float points[] = {
            0.0f,  0.5f,  0.0f,
            0.5f, -0.5f,  0.0f,
            -0.5f, -0.5f,  0.0f
    };

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 0, NULL);

    // Vertex Shader
    const char* vertex_shader =
            "#version 400\n"
            "in vec3 vp;"
            "void main () {"
            "  gl_Position = vec4 (vp, 1.0);"
            "}";

    // Fragment Shader
    const char* fragment_shader =
            "#version 400\n"
                    "out vec4 frag_colour;"
                    "void main () {"
                    "  frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
                    "}";

    // Compile Shaders
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    // Combine
    GLuint shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme); // now everything okay to draw

    while (!glfwWindowShouldClose(window)) {
        // Game Logic here
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // Drawing triangle
        glUseProgram(shader_programme);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Delete
    glDeleteProgram(shader_programme);
    glDeleteShader(fs);
    glDeleteShader(vs);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}