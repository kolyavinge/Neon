#pragma once

#include <ui/Screens.h>

class IScreenSwitcher {

public:
    virtual ~IScreenSwitcher() {}
    void virtual switchTo(Screens screen) = 0;
};
