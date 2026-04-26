#include <core/Game.h>

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
}
