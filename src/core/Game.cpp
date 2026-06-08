#include <core/Game.h>
#include <core/MainInjectModule.h>
#include <lib/di/DependencyContainer.h>
#include <render/lib/opengl.h>

Game::Game(
    InputManager& inputManager,
    ScreenManager& screenManager,
    GameInitializer& gameInitializer) :
    _inputManager(inputManager),
    _screenManager(screenManager),
    _gameInitializer(gameInitializer) {
}

void Game::init() {
    _gameInitializer.initGame(_gameState);
}

void Game::update() {
    _inputManager.updateInputDevices();
    _screenManager.getCurrentScreen().update();
    //_screenManager.getCurrentScreenVox().vox();
}

void Game::render() {
    _screenManager.getCurrentScreenRenderer().render();
    if (glGetError() != GL_NO_ERROR) throw OpenGLException(L"");
}

Game& GameFactory::make() {
    DependencyContainer container;
    container.initFrom<MainInjectModule>();

    Game& game = container.resolve<Game>();
    game.init();

    return game;
}
