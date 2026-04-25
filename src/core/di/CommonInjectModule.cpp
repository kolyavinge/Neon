#include <core/DrivingInputManager.h>
#include <core/Game.h>
#include <core/InputManager.h>
#include <core/ScreenManager.h>
#include <core/di/CommonInjectModule.h>
#include <ui/DebugScreen.h>

void CommonInjectModule::init(Binder& binder) {
    binder.bindSingleton<DrivingInputManager>(DrivingInputManager::resolve);
    binder.bindSingleton<Game>(Game::resolve);
    binder.bindSingleton<InputManager>();
    binder.bindSingleton<ScreenManager>(ScreenManager::resolve);
    binder.bindSingleton<DebugScreen>(DebugScreen::resolve);
}
