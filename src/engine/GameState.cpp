#include <engine/GameState.h>

GameState::GameState() {
    init();
}

void GameState::init() {
    for (int i = 0; i < vehicles.getCount(); i++) {
        vehicles[i].init();
    }
}
