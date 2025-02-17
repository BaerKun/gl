#include <iostream>

#include "glad/glad.h"
#include "window.hpp"
#include "shader.hpp"
#include "object.hpp"

static void keyCallback(GLFWwindow *, int, int, int, int);

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
};

GLObject createTriangle(){
    Shader vertexShader(GL_VERTEX_SHADER);
    vertexShader.load("../GLSL/vertex0.glsl");
    Shader fragmentShader(GL_FRAGMENT_SHADER);
    fragmentShader.load("../GLSL/fragment0.glsl");
    auto program = new ShaderProgram(vertexShader, fragmentShader);

    auto vbo = new VertexBuffer;
    vbo->loadData(vertices, sizeof(vertices));
    auto vao = new VertexArray;
    vao->setVertexAttribute(0, 3, GL_FLOAT, sizeof(float) * 3, 0);

    return {program, vbo, vao};
}

int main(){
    Window window(800, 600, "learn-GL");
    window.setKeyCallback(&keyCallback);

    GLObject triangle = createTriangle();

    while (!window.shouldClose()){
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        triangle.draw(GL_TRIANGLES, 3);

        window.refresh();
    }
    glfwTerminate();
    return 0;
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode){
    std::cout << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}