#include <core/GameFactory.h>
#include <core/di/MainDependencyContainer.h>

Game& GameFactory::make() {
    MainDependencyContainer container;
    Game& game = container.resolve<Game>();
    game.init();

    return game;
}
