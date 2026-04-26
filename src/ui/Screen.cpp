#include <ui/Screen.h>

Screen::Screen() {
    _screenSwitcher = nullptr;
}

void Screen::setScreenSwitcher(IScreenSwitcher& screenSwitcher) {
    _screenSwitcher = &screenSwitcher;
}
