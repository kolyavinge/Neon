#include <core/DrivingInputManager.h>

DrivingInputManager::DrivingInputManager(
    InputManager& inputManager) :
    _inputManager(inputManager) {
}

void DrivingInputManager::update(DrivingInputData& inputData) {
    if (_inputManager.keyboard.isKeyPressedOrHeld(Keys::a)) {
        inputData.setSteeringRatio(-1.0f);
    } else if (_inputManager.keyboard.isKeyPressedOrHeld(Keys::d)) {
        inputData.setSteeringRatio(1.0f);
    } else {
        inputData.setSteeringRatio(0.0f);
    }

    if (_inputManager.keyboard.isKeyPressedOrHeld(Keys::w)) {
        inputData.setThrottleRatio(1.0f);
    } else if (_inputManager.keyboard.isKeyReleased(Keys::w)) {
        inputData.setThrottleRatio(0.0f);
    }

    // debug only
    if (_inputManager.keyboard.isKeyPressed(Keys::e)) {
        inputData.addThrottleRatio(0.05f);
    } else if (_inputManager.keyboard.isKeyPressed(Keys::q)) {
        inputData.addThrottleRatio(-0.05f);
    }
    // debug only

    if (_inputManager.keyboard.isKeyPressedOrHeld(Keys::s)) {
        inputData.setBrakeRatio(1.0f);
    } else {
        inputData.setBrakeRatio(0.0f);
    }

    inputData.resetShifting();
    if (_inputManager.keyboard.isKeyPressed(Keys::up)) {
        inputData.shiftUp();
    } else if (_inputManager.keyboard.isKeyPressed(Keys::down)) {
        inputData.shiftDown();
    }
}
