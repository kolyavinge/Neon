#include <core/Game.h>
#include <core/MainInjectModule.h>
#include <lib/di/DependencyContainer.h>

Game::Game(
    InputManager& inputManager,
    ScreenManager& screenManager,
    GameInitializer& gameInitializer,
    RenderDebuger& renderDebuger) :
    _inputManager(inputManager),
    _screenManager(screenManager),
    _gameInitializer(gameInitializer),
    _renderDebuger(renderDebuger) {
}

void Game::init() {
    _gameInitializer.initGame();
    _gameInitializer.initGameWorld(_gameWorld);
}

void Game::update() {
    _inputManager.updateInputDevices();
    _screenManager.getCurrentScreen().update();
    //_screenManager.getCurrentScreenVox().vox();
}

void Game::render() {
    _screenManager.getCurrentScreenRenderer().render();
    _renderDebuger.print(_gameWorld);
}

Game& GameFactory::make() {
    DependencyContainer container;
    container.initFrom<MainInjectModule>();

    Game& game = container.resolve<Game>();
    game.init();

    return game;
}
