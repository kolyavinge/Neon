#include <App.h>
#include <common/constants.h>
#include <core/Game.h>
#include <debug/stat.h>

void App::onKeyInput(GLFWwindow* window, int key, int, int action, int) noexcept {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void App::run() {
    if (glfwInit() == GLFW_FALSE) throw AppException();
    GLFWwindow* window = glfwCreateWindow(CommonConstants::screenWidth, CommonConstants::screenHeight, CommonConstants::title, nullptr, nullptr);
    if (window == nullptr) { glfwTerminate(); throw AppException(); }
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (mode->width - CommonConstants::screenWidth) / 2, (mode->height - CommonConstants::screenHeight) / 2);
    glfwSetKeyCallback(window, App::onKeyInput);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) throw AppException();
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
    //showDebugInfo();

    App::run();

    return 0;
}
