#include "window.hpp"
#include <iostream>


Window::Window(const int width, const int height, const char *name) {
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
    _window = glfwCreateWindow(width, height, name, nullptr, nullptr);

    if (_window == nullptr) {
        std::cerr << "Error: Failed to create GLFW window";
        return;
    }
    // 设置窗口上下文
    glfwMakeContextCurrent(_window);

    // 初始化GLAD
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Error: Failed to initialize GLAD";
    }
}