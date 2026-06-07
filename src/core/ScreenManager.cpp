#include <core/ScreenManager.h>

ScreenManager::ScreenManager(
    RaceScreen& debugScreen,
    RaceScreenRenderer& raceScreenRenderer) {
    _screens[(int)Screens::race] = &debugScreen;
    debugScreen.setScreenSwitcher(*this);
    _screenRenderers[(int)Screens::race] = &raceScreenRenderer;
    raceScreenRenderer.setScreen(debugScreen);
    _currentScreen = Screens::race;
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
