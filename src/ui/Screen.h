#pragma once

#include <lib/system.h>
#include <ui/IScreenSwitcher.h>

class Screen : public Object {

public:
    IScreenSwitcher* screenSwitcher = nullptr;

    void virtual update() = 0;
};
