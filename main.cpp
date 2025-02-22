#include <iostream>

#include "texture.hpp"
#include "glad/glad.h"
#include "window.hpp"
#include "shader.hpp"
#include "vertex.hpp"

static void keyCallback(GLFWwindow *, int, int, int, int);

float vertices[] = {
    0.8f, 0.8f, 0.0f, 1.f, 1.f,
    -0.8f, 0.8f, 0.0f, 0.f, 1.f,
    -0.8f, -0.8f, 0.0f, 0.f, 0.f,
    0.8f, -0.8f, 0.0f, 1.f, 0.f
};

unsigned elements[] = {
    0, 1, 2,
    2, 3, 0
};

int main() {
    Window window(800, 600, "learn-GL");
    window.setKeyCallback(&keyCallback);

    const Texture2D happy("../img/happy_face.png");
    const Texture2D container("../img/container.jpg");

    const ShaderProgram program(
        Shader(GL_VERTEX_SHADER, Shader::loadSource("../glsl/vert0.glsl").c_str()),
        Shader(GL_FRAGMENT_SHADER, Shader::loadSource("../glsl/frag0.glsl").c_str()));

    const VertexSet triangle(vertices, 4, {3, 2});
    const ElementBuffer ebo(elements, sizeof(unsigned) * 6);

    while (!window.shouldClose()) {
        // FPS通常取决于显示器刷新率
        const double deltaTime = window.getDeltaTime();
        std::printf("\rFPS: %.3lf    ", 1. / deltaTime);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();

        program.use();
        happy.bind(0);
        container.bind(1);
        program.setUniform("tex0", 0);
        program.setUniform("tex1", 1);
        triangle.draw(GL_TRIANGLES, 6, &ebo);

        window.refresh();
    }
    glfwTerminate();
    return 0;
}

static void keyCallback(GLFWwindow *window, const int key, const int scancode, const int action, const int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
