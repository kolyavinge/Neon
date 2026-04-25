#include <common/DrivingInputManager.h>
#include <common/InputManager.h>
#include <core/Game.h>
#include <core/ScreenManager.h>
#include <core/di/GameInjectModule.h>
#include <ui/DebugScreen.h>

void GameInjectModule::init(Binder& binder) {
    binder.bindSingleton<InputManager>();
    binder.bindSingleton<DrivingInputManager>(DrivingInputManager::resolve);

    binder.bindSingleton<ScreenManager>(ScreenManager::resolve);
    binder.bindSingleton<DebugScreen>(DebugScreen::resolve);

    binder.bindSingleton<Game>(Game::resolve);
}
