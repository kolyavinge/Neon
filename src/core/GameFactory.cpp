#include <core/GameFactory.h>
#include <core/MainInjectModule.h>
#include <lib/di/DependencyContainer.h>

Game& GameFactory::make() {
    DependencyContainer container;
    container.initFrom<MainInjectModule>();

    Game& game = container.resolve<Game>();
    game.init();

    return game;
}
