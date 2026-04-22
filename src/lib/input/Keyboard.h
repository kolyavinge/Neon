#pragma once

#include <lib/input/InputDevice.h>
#include <lib/system.h>

class Keyboard : public InputDevice {

    Array<unsigned char, 256> _winKeyStates;

protected:
    void updatePressedKeys();

private:
    bool isKeyPressed(unsigned char keyState);
};
