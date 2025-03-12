#ifndef GL_WINDOW_HPP
#define GL_WINDOW_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"


typedef struct {
    bool keyboard[GLFW_KEY_LAST + 1];
    int key;
    int action;
} KeyState;

typedef struct {
    double x, y;
    double scrollX, scrollY;
    int button;
    int action;
} MouseState;


class Window {
public:
    Window(int width, int height, const char *name);

    void refresh() {
        glfwSwapBuffers(window_);

        const double currentTime = glfwGetTime();
        deltaTime_ = currentTime - lastFrameTime_;
        lastFrameTime_ = currentTime;
    }

    static void updateInputState();

    bool shouldClose() const {
        return glfwWindowShouldClose(window_);
    }

    void close() const {
        glfwSetWindowShouldClose(window_, GLFW_TRUE);
    }

    double getDeltaTime() const {
        return deltaTime_;
    }

    const KeyState &getKeyState() const {
        return keyState_;
    }

    const MouseState &getMouseState() const {
        return mouseState_;
    }

private:
    GLFWwindow *window_;
    double lastFrameTime_ = 0.;
    double deltaTime_ = 0.;
    KeyState &keyState_;
    MouseState &mouseState_;
};

#endif //GL_WINDOW_HPP
