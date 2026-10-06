#include <App.h>
#include <common/constants.h>
#include <core/Game.h>
#include <float.h>
#include <lib/windows.h>

bool App::_isFullScreenActive = false;

void App::moveConsoleToCorner() {
    HWND cmdWnd = GetConsoleWindow();
    if (cmdWnd != nullptr) {
        int xPos = 0;
        int yPos = 0;
        int width = 800;
        int height = 800;
        MoveWindow(cmdWnd, xPos, yPos, width, height, true);
    }
}

void App::setFullScreenMode(GLFWwindow* window) {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
}

void App::setWindowedMode(GLFWwindow* window) {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowMonitor(window, NULL,
        (mode->width - CommonConstants::screenWidth) / 2 + 350, (mode->height - CommonConstants::screenHeight) / 2,
        CommonConstants::screenWidth, CommonConstants::screenHeight,
        GLFW_DONT_CARE);
}

void App::onResize(GLFWwindow*, int width, int) noexcept {
    glViewport(0, 0, width, (int)((float)width / CommonConstants::screenAspect));
}

void App::onKeyInput(GLFWwindow* window, int key, int, int action, int) noexcept {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS) {
        if (_isFullScreenActive) {
            setWindowedMode(window);
        } else {
            setFullScreenMode(window);
        }
        _isFullScreenActive = !_isFullScreenActive;
    }
}

void App::run() {
    if (glfwInit() == GLFW_FALSE) throw AppException();
    GLFWwindow* window = glfwCreateWindow(CommonConstants::screenWidth, CommonConstants::screenHeight, CommonConstants::title, nullptr, nullptr);
    if (window == nullptr) { glfwTerminate(); throw AppException(); }
    setWindowedMode(window);
    glfwSetKeyCallback(window, onKeyInput);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, onResize);
    if (glewInit() != GLEW_OK) throw AppException();
    moveConsoleToCorner();
    Game& game = GameFactory::make();
    double lastTime = glfwGetTime();
    double accumulator = 0.0;
    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        accumulator += currentTime - lastTime;
        lastTime = currentTime;
        if (accumulator >= CommonConstants::deltaTimeSec) {
            game.update();
            game.render();
            accumulator -= CommonConstants::deltaTimeSec;
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
}

int main(int, char**) {
    unsigned int state;
    _controlfp_s(&state, 0, _EM_ZERODIVIDE | _EM_INVALID); // аппаратные исключения

    App::run();

    return 0;
}
