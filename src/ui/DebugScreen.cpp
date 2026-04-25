#include <ui/DebugScreen.h>

DebugScreen::DebugScreen(
    GameUpdater& gameUpdater) :
    _gameUpdater(gameUpdater) {
}

void DebugScreen::update() {
    _gameUpdater.update();
}
