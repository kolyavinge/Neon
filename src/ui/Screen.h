#pragma once

#include <lib/system.h>
#include <ui/IScreenSwitcher.h>

enum class Screens {
    start,
    race,
    pause,
    debug,
    _count
};

class Screen : public Object {

public:
    IScreenSwitcher* screenSwitcher = nullptr;

    void virtual update() = 0;
};
