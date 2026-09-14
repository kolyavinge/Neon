#pragma once

#include <lib/input/InputDevice.h>
#include <lib/system.h>

class Joystick : public InputDevice {

public:

protected:
    void updatePressedKeys();
};
