#include <core/Game.h>

Game::Game(
    InputManager& inputManager,
    ScreenManager& screenManager,
    GameUpdater& gameUpdater) :
    _inputManager(inputManager),
    _screenManager(screenManager),
    _gameUpdater(gameUpdater) {
}

void Game::init() {
    _gameState.init();
    _gameUpdater.init(_gameState);
}

void Game::update() {
    _inputManager.updateInputDevices();
    _screenManager.getCurrentScreen().update();
    //_screenManager.getCurrentScreenVox().vox();
}

void Game::render() {
    _screenManager.getCurrentScreenRenderer().render();
}
