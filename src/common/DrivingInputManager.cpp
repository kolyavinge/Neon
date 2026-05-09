#include <common/DrivingInputManager.h>

DrivingInputManager::DrivingInputManager(
    InputManager& inputManager) :
    _inputManager(inputManager) {
}

void DrivingInputManager::update(DrivingInputData& inputData) {
    inputData.reset();

    if (_inputManager.keyboard.isKeyPressedOrHeld(Keys::a)) {
        inputData.setSteeringRatio(-1.0f);
    } else if (_inputManager.keyboard.isKeyPressedOrHeld(Keys::d)) {
        inputData.setSteeringRatio(1.0f);
    }

    if (_inputManager.keyboard.isKeyPressedOrHeld(Keys::w)) {
        inputData.setThrottleRatio(1.0f);
    } else if (_inputManager.keyboard.isKeyPressedOrHeld(Keys::s)) {
        inputData.setBrakeRatio(1.0f);
    }

    if (_inputManager.keyboard.isKeyPressed(Keys::up)) {
        inputData.shiftUp();
    } else if (_inputManager.keyboard.isKeyPressed(Keys::down)) {
        inputData.shiftDown();
    }
}
