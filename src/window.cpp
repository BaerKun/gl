#include "window.hpp"
#include <iostream>

KeyState Window::keyState_{};
MouseState Window::mouseState_{};
GLFWwindow *Window::glfwWindow_ = nullptr;
double Window::lastFrameTime_ = 0.;
double Window::deltaTime_ = 0.;


void Window::setCallback(GLFWwindow *window) {
    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods){
        if (action == GLFW_PRESS)
            keyState_.keyboard[key] = true;
        else if (action == GLFW_RELEASE)
            keyState_.keyboard[key] = false;
        keyState_.key = key;
        keyState_.action = action;
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow *window, double x, double y){
        mouseState_.x = x;
        mouseState_.y = y;
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods){
        mouseState_.button = button;
        mouseState_.action = action;
    });

    glfwSetScrollCallback(window, [](GLFWwindow *window, double x, double y){
        mouseState_.scrollX = x;
        mouseState_.scrollY = y;
    });
}

void Window::init(const int width, const int height, const char name[]) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    if (glfwWindow_ != nullptr)
        return;

    glfwWindow_ = glfwCreateWindow(width, height, name, nullptr, nullptr);

    if (glfwWindow_ == nullptr) {
        std::cerr << "Error: Failed to create GLFW window";
        return;
    }

    glfwMakeContextCurrent(glfwWindow_);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Error: Failed to initialize GLAD";
        return;
    }

    setCallback(glfwWindow_);
}

void Window::updateInputState() {
    keyState_.key = keyState_.action = -1;
    mouseState_.button = mouseState_.action = -1;
    mouseState_.scrollX = mouseState_.scrollY = 0.;
    glfwPollEvents();
}