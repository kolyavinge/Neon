#pragma once

#include <lib/input/Keyboard.h>
#include <lib/system.h>

class InputManager : public Object {

public:
    Keyboard keyboard;

    void updateInputDevices();
};
