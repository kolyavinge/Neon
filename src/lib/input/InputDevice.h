#pragma once

#include <lib/system.h>

enum class Keys {
    up,
    down,
    left,
    right,
    w,
    a,
    s,
    d,
    q,
    e,
    space,
    enter,
    escape,
    backspace,
    button1,
    button2,
    button3,
    button4,
    button5,
    button6,
    button7,
    button8,
    start,
    select,
    _count
};

enum class KeyStates {
    unpressed,
    pressed,
    held,
    released
};

class InputDevice : public Object {

    Array<KeyStates, (int)Keys::_count> _keyStates;

public:
    InputDevice();
    bool isKeyUnpressed(Keys key);
    bool isKeyPressed(Keys key);
    bool isKeyHeld(Keys key);
    bool isKeyPressedOrHeld(Keys key);
    bool isKeyReleased(Keys key);
    void update();

protected:
    Array<bool, (int)Keys::_count> _pressedKeys;

    void virtual updatePressedKeys() = 0;
};
