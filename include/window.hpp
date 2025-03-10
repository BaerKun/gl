#ifndef GL_WINDOW_HPP
#define GL_WINDOW_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"

typedef void (*KeyCallback)(GLFWwindow *window, int key, int scancode, int action, int mods);

typedef void (*CursorPosCallback)(GLFWwindow *window, double xpos, double ypos);

class Window {
public:
    explicit Window(GLFWwindow *window) {
        _window = window;
    }

    Window(int width, int height, const char *name);

    void refresh() {
        glfwSwapBuffers(_window);

        const double currentTime = glfwGetTime();
        _deltaTime = currentTime - _lastFrameTime;
        _lastFrameTime = currentTime;
    }

    bool shouldClose() const {
        return glfwWindowShouldClose(_window);
    }

    void close() const {
        glfwSetWindowShouldClose(_window, GLFW_TRUE);
    }

    void setKeyCallback(const KeyCallback callback) const {
        glfwSetKeyCallback(_window, callback);
    }

    void setCursorPosCallback(const CursorPosCallback callback) const {
        glfwSetCursorPosCallback(_window, callback);
    }

    double getDeltaTime() const {
        return _deltaTime;
    }

private:
    GLFWwindow *_window;
    double _lastFrameTime = 0.;
    double _deltaTime = 0.;
};

#endif //GL_WINDOW_HPP
