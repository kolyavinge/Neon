#pragma once

#include <glfw/glfw3.h>
#include <lib/system.h>

class AppException : public Exception {};

class App : public Object {

public:
    void static onKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept;
    void static run();
};
