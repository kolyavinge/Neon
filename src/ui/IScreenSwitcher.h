#pragma once

#include <ui/Screen.h>

class IScreenSwitcher {

public:
    void virtual switchTo(Screens screen) = 0;
};
