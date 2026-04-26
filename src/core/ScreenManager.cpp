#include <core/ScreenManager.h>

ScreenManager::ScreenManager(
    DebugScreen& debugScreen,
    DebugScreenRenderer& debugScreenRenderer) {
    _screens[(int)Screens::debug] = &debugScreen;
    debugScreen.setScreenSwitcher(*this);

    _screenRenderers[(int)Screens::debug] = &debugScreenRenderer;
    debugScreenRenderer.setScreen(debugScreen);

    _currentScreen = Screens::debug;
}

Screen& ScreenManager::getCurrentScreen() {
    return *_screens[(int)_currentScreen];
}

ScreenRenderer& ScreenManager::getCurrentScreenRenderer() {
    return *_screenRenderers[(int)_currentScreen];
}

void ScreenManager::switchTo(Screens screen) {
    _currentScreen = screen;
}
