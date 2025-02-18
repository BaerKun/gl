#include <iostream>

#include "glad/glad.h"
#include "window.hpp"
#include "shader.hpp"
#include "vertex.hpp"

static void keyCallback(GLFWwindow *, int, int, int, int);

float vertices[] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        1.0f, 0.5f, 0.0f
};

unsigned elements[] = {
        0, 1, 2,
        2, 3, 0
};

int main() {
    const Window window(800, 600, "learn-GL");
    window.setKeyCallback(&keyCallback);

    const ShaderProgram program(
            Shader(GL_VERTEX_SHADER, Shader::loadSource("../glsl/vert0.glsl").c_str()),
            Shader(GL_FRAGMENT_SHADER, Shader::loadSource("../glsl/frag0.glsl").c_str()));

    const VertexSet triangle(vertices, 4, {3});
    const ElementBuffer ebo(elements, sizeof(unsigned) * 6);

    while (!window.shouldClose()) {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.use();
        triangle.draw(GL_TRIANGLES, 6, &ebo);

        window.refresh();
    }
    glfwTerminate();
    return 0;
}

static void keyCallback(GLFWwindow *window, const int key, const int scancode, const int action, const int mode) {
    std::cout << key << std::endl;
    static float red[] = {1.f, 0.f, 0.f};
    static float green[] = {0.f, 1.f, 0.f};
    static float blue[] = {0.f, 0.f, 1.f};
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
        currShaderProgram->setUniformVec("color_", red, 3);
    if (key == GLFW_KEY_G && action == GLFW_PRESS)
        currShaderProgram->setUniformVec("color_", green, 3);
    if (key == GLFW_KEY_B && action == GLFW_PRESS)
        currShaderProgram->setUniformVec("color_", blue, 3);
}