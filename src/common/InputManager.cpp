#include <common/InputManager.h>

void InputManager::updateInputDevices() {
    joystick.update();
    keyboard.update();
}
