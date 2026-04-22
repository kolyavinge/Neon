#include <lib/input/InputDevice.h>

InputDevice::InputDevice() {
    _keyStates.initAll(KeyStates::unpressed);
}

bool InputDevice::isKeyUnpressed(Keys key) {
    return _keyStates[(int)key] == KeyStates::unpressed;
}

bool InputDevice::isKeyPressed(Keys key) {
    return _keyStates[(int)key] == KeyStates::pressed;
}

bool InputDevice::isKeyHeld(Keys key) {
    return _keyStates[(int)key] == KeyStates::held;
}

bool InputDevice::isKeyPressedOrHeld(Keys key) {
    return isKeyPressed(key) || isKeyHeld(key);
}

bool InputDevice::isKeyReleased(Keys key) {
    return _keyStates[(int)key] == KeyStates::released;
}

void InputDevice::update() {
    _pressedKeys.initAll(false);
    updatePressedKeys();
    for (int i = 0; i < _keyStates.getCount(); i++) {
        KeyStates currentState = _keyStates[i];
        bool isPressed = _pressedKeys[i];
        if (currentState == KeyStates::unpressed && isPressed) _keyStates[i] = KeyStates::pressed;
        else if (currentState == KeyStates::pressed && isPressed) _keyStates[i] = KeyStates::held;
        else if (currentState == KeyStates::pressed && !isPressed) _keyStates[i] = KeyStates::released;
        else if (currentState == KeyStates::held && !isPressed) _keyStates[i] = KeyStates::released;
        else if (currentState == KeyStates::released && isPressed) _keyStates[i] = KeyStates::pressed;
        else if (currentState == KeyStates::released && !isPressed) _keyStates[i] = KeyStates::unpressed;
    }
}
