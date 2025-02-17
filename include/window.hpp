#ifndef OPENGL_INIT_WINDOW_HPP
#define OPENGL_INIT_WINDOW_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"

typedef void (*KeyCallback)(GLFWwindow *window, int key, int scancode, int action, int mods);

class Window {
public:
    Window(int width, int height, const char *name);

    inline void refresh() {
        glfwSwapBuffers(_window);
    }

    inline bool shouldClose() {
        return glfwWindowShouldClose(_window);
    }

    inline void setKeyCallback(KeyCallback callback) {
        glfwSetKeyCallback(_window, callback);
    }

private:
    GLFWwindow *_window;
    int _width, _height;
    const char *_name;
};

#endif //OPENGL_INIT_WINDOW_HPP
