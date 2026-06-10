#pragma once

// в glfw3.h подключается gl.h, glew.h нужно подключить раньше
#include <glew/glew.h>

#include <glfw/glfw3.h>
#include <lib/system.h>

class AppException : public Exception {};

class App : public Object {

public:
    void static run();

private:
    void static onResize(GLFWwindow* window, int width, int height) noexcept;
    void static onKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept;
};
