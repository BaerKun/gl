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
    Window() = default;

    static void init(int width, int height, const char name[]);

    static void refresh() {
        glfwSwapBuffers(glfwWindow_);

        const double currentTime = glfwGetTime();
        deltaTime_ = currentTime - lastFrameTime_;
        lastFrameTime_ = currentTime;
    }

    static void updateInputState();

    static bool shouldClose() {
        return glfwWindowShouldClose(glfwWindow_);
    }

    static void close() {
        glfwSetWindowShouldClose(glfwWindow_, GLFW_TRUE);
    }

    static double getDeltaTime() {
        return deltaTime_;
    }

    static const KeyState &getKeyState() {
        return keyState_;
    }

    static const MouseState &getMouseState() {
        return mouseState_;
    }

private:
    static void setCallback(GLFWwindow *window);

    static KeyState keyState_;
    static MouseState mouseState_;
    static GLFWwindow *glfwWindow_;
    static double lastFrameTime_;
    static double deltaTime_;
};

#endif //GL_WINDOW_HPP
