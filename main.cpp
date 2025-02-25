#include <camera.hpp>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include "texture.hpp"
#include "glad/glad.h"
#include "window.hpp"
#include "shader.hpp"
#include "vertex.hpp"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

static void keyCallback(GLFWwindow *, int, int, int, int);

static void cursorPosCallback(GLFWwindow *, double, double);

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned elements[] = {
    0, 1, 2,
    2, 3, 0
};

Camera camera;

int main() {
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "learn-GL");
    window.setKeyCallback(&keyCallback);
    window.setCursorPosCallback(&cursorPosCallback);

    const Texture2D happy("../img/happy_face.png");
    const Texture2D container("../img/container.jpg");

    const ShaderProgram program(
        Shader(GL_VERTEX_SHADER, Shader::loadSource("../glsl/vert0.glsl").c_str()),
        Shader(GL_FRAGMENT_SHADER, Shader::loadSource("../glsl/frag0.glsl").c_str()));

    program.use();
    happy.bind(0);
    container.bind(1);
    program.setUniform("tex0", 0);
    program.setUniform("tex1", 1);

    const VertexSet cube(vertices, 36, {3, 2});
    const ElementBuffer ebo(elements, sizeof(unsigned) * 6);

    camera.setPerspective(45.f, static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT, 0.1f, 100.f);

    glEnable(GL_DEPTH_TEST);
    while (!window.shouldClose()) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwPollEvents();

        program.setUniformMat("transform", glm::value_ptr(camera.getMatrix()), 4);
        cube.draw(GL_TRIANGLES, 36);

        window.refresh();
    }
    glfwTerminate();
    return 0;
}

static void keyCallback(GLFWwindow *window, const int key, const int scancode, const int action, const int mode) {
    static bool keyboard[512] = {false};

    const Window w(window);

    if (action == GLFW_PRESS)
        keyboard[key] = true;
    else if (action == GLFW_RELEASE)
        keyboard[key] = false;

    if (keyboard[GLFW_KEY_ESCAPE])
        w.close();

    constexpr float speed = 0.05f;
    glm::vec3 t{};

    if (keyboard[GLFW_KEY_W])
        t.z += speed;
    if (keyboard[GLFW_KEY_S])
        t.z -= speed;
    if (keyboard[GLFW_KEY_A])
        t.x -= speed;
    if (keyboard[GLFW_KEY_D])
        t.x += speed;
    camera.move(t);

    if (keyboard[GLFW_KEY_SPACE])
        camera.lookAt(glm::vec3(0, 0, 0));
}

static void cursorPosCallback(GLFWwindow *window, const double x, const double y) {
    static double lastX = 0, lastY = 0;
    if (lastX == 0 && lastY == 0) {
        lastX = x;
        lastY = y;
        return;
    }

    camera.rotate(glm::vec3(y - lastY, x - lastX, 0), 0.002);
    lastX = x;
    lastY = y;
}
