#include <App.h>
#include <common/constants.h>
#include <core/Game.h>
#include <lib/windows.h>
#include <lib/calc/CoordinateAxes.h>

void App::onResize(GLFWwindow*, int width, int) noexcept {
    glViewport(0, 0, width, (int)((float)width / CommonConstants::screenAspect));
}

void App::onKeyInput(GLFWwindow* window, int key, int, int action, int) noexcept {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

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

void App::run() {
    if (glfwInit() == GLFW_FALSE) throw AppException();
    GLFWwindow* window = glfwCreateWindow(CommonConstants::screenWidth, CommonConstants::screenHeight, CommonConstants::title, nullptr, nullptr);
    if (window == nullptr) { glfwTerminate(); throw AppException(); }
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (mode->width - CommonConstants::screenWidth) / 2 + 350, (mode->height - CommonConstants::screenHeight) / 2);
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
    App::run();
    return 0;
}
