#pragma once

#include <lib/input/Joystick.h>
#include <lib/input/Keyboard.h>
#include <lib/system.h>

class InputManager : public Object {

public:
    Joystick joystick;
    Keyboard keyboard;

    void updateInputDevices();
};
