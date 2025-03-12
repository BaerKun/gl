#include "window.hpp"
#include <iostream>

KeyState keyState;

MouseState mouseState;

static void setCallback(GLFWwindow *window) {
    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods){
        if (action == GLFW_PRESS)
            keyState.keyboard[key] = true;
        else if (action == GLFW_RELEASE)
            keyState.keyboard[key] = false;
        keyState.key = key;
        keyState.action = action;
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow *window, double x, double y){
        mouseState.x = x;
        mouseState.y = y;
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods){
        mouseState.button = button;
        mouseState.action = action;
    });

    glfwSetScrollCallback(window, [](GLFWwindow *window, double x, double y){
        mouseState.scrollX = x;
        mouseState.scrollY = y;
    });
}

Window::Window(const int width, const int height, const char *name) : keyState_(keyState), mouseState_(mouseState) {
    // 初始化GLFW
    glfwInit();

    // 设置OpenGL版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // 设置OpenGL为核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // 创建窗口
    window_ = glfwCreateWindow(width, height, name, nullptr, nullptr);

    if (window_ == nullptr) {
        std::cerr << "Error: Failed to create GLFW window";
        return;
    }
    // 设置窗口上下文
    glfwMakeContextCurrent(window_);

    // 初始化GLAD
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Error: Failed to initialize GLAD";
        return;
    }

    setCallback(window_);
}

void Window::updateInputState() {
    keyState.key = keyState.action = -1;
    mouseState.button = mouseState.action = -1;
    mouseState.scrollX = mouseState.scrollY = 0.;
    glfwPollEvents();
}