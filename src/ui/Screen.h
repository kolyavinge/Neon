#pragma once

#include <lib/system.h>
#include <ui/IScreenSwitcher.h>

class Screen : public Object {

protected:
    IScreenSwitcher* _screenSwitcher;

public:
    Screen();
    void setScreenSwitcher(IScreenSwitcher& screenSwitcher);
    void virtual update() = 0;
};
