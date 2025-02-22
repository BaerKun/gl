#ifndef GL_WINDOW_HPP
#define GL_WINDOW_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shader.hpp"

typedef void (*KeyCallback)(GLFWwindow *window, int key, int scancode, int action, int mods);

class Window {
public:
    Window(int width, int height, const char *name);

    void refresh() const {
        glfwSwapBuffers(_window);
    }

    bool shouldClose() const {
        return glfwWindowShouldClose(_window);
    }

    void setKeyCallback(const KeyCallback callback) const {
        glfwSetKeyCallback(_window, callback);
    }

    double getDeltaTime() {
        const double currFrameTime = glfwGetTime();
        const double deltaTime = currFrameTime - _lastFrameTime;
        _lastFrameTime = currFrameTime;
        return deltaTime;
    }

private:
    GLFWwindow *_window;
    double _lastFrameTime = 0.;
};

#endif //GL_WINDOW_HPP
