#pragma once

// в glfw3.h подключается gl.h, glew.h нужно подключить раньше
#include <glew/glew.h>

#include <core/Game.h>
#include <glfw/glfw3.h>
#include <lib/system.h>

class AppException : public Exception {};

class App : public Object {

    static Game* _game;
    static bool _isFullScreenActive;

public:
    void static run();

private:
    static GLFWwindow* initMainWindow();
    static void moveConsoleToCorner();
    static void setFullScreenMode(GLFWwindow* window);
    static void setWindowedMode(GLFWwindow* window);
    static void onResize(GLFWwindow* window, int width, int height) noexcept;
    static void onKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept;
};
