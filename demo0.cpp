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

constexpr float vertices[] = {
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

constexpr unsigned elements[] = {
    0, 1, 2,
    2, 3, 0
};

Camera camera;
Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "learn-GL");

static void processInput();

int main() {
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

        Window::updateInputState();
        processInput();

        program.setUniformMat("transform", glm::value_ptr(camera.getMatrix()), 4);
        cube.draw(GL_TRIANGLES, 36);

        window.refresh();
    }
    glfwTerminate();
    return 0;
}

static void processInput(){
    const KeyState &keyState = window.getKeyState();
    const MouseState &mouseState = window.getMouseState();
    const auto deltaTime = (float)window.getDeltaTime();

    if(keyState.key == GLFW_KEY_ESCAPE)
        window.close();

    if(keyState.keyboard[GLFW_KEY_SPACE]) {
        camera.lookAt(glm::vec3());
    }else {
        glm::vec3 translate;
        const float deltaMove = deltaTime * 1.f;
        if (keyState.keyboard[GLFW_KEY_D])
            translate.x = deltaMove;
        if (keyState.keyboard[GLFW_KEY_A])
            translate.x -= deltaMove;
        if (keyState.keyboard[GLFW_KEY_W])
            translate.y = deltaMove;
        if (keyState.keyboard[GLFW_KEY_S])
            translate.y -= deltaMove;
        translate.z = (float) mouseState.scrollY * deltaTime * 2.f;
        camera.move(translate);
    }

    static double lastX = 0, lastY = 0;
    if (lastX == 0){
        lastX = mouseState.x;
        lastY = mouseState.y;
        return;
    }
    // mouseState.x/y 是像素坐标
    const glm::vec3 axis(mouseState.y - lastY, mouseState.x - lastX, 0);
    const float deltaAngle = deltaTime * std::sqrtf(axis.x * axis.x + axis.y * axis.y) * 0.1f;

    if(deltaAngle != 0.)
        camera.rotate(axis, deltaAngle);

    lastX = mouseState.x;
    lastY = mouseState.y;
}
