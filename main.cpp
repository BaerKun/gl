#include <iostream>

#include "glad/glad.h"
#include "window.hpp"
#include "shader.hpp"
#include "vertex.hpp"

static void keyCallback(GLFWwindow *, int, int, int, int);

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
};

int main(){
    const Window window(800, 600, "learn-GL");
    window.setKeyCallback(&keyCallback);

    const Shader vertexShader(GL_VERTEX_SHADER);
    vertexShader.load("../glsl/vert0.glsl");
    const Shader fragmentShader(GL_FRAGMENT_SHADER);
    fragmentShader.load("../glsl/frag0.glsl");
    const ShaderProgram program(vertexShader, fragmentShader);

    const VertexBuffer vbo(vertices, sizeof(vertices));
    const VertexArray vao;
    vao.setVertexAttribute(0, 3, GL_FLOAT, sizeof(float) * 3, 0);

    const VertexSet triangle(&vbo, &vao);

    while (!window.shouldClose()){
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.use();
        triangle.draw(GL_TRIANGLES, 3);

        window.refresh();
    }
    glfwTerminate();
    return 0;
}

static void keyCallback(GLFWwindow *window, const int key, const int scancode, const int action, const int mode){
    std::cout << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}