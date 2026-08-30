#include <common/constants.h>
#include <core/PlayerInputManager.h>
#include <lib/calc/Math.h>
#include <model/vehicle/DrivingInputData.h>
#include <model/vehicle/Gear.h>
#include <model/vehicle/VehicleData.h>
#include <model/vehicle/Wheel.h>

PlayerInputManager::PlayerInputManager(
    InputManager& inputManager) :
    _inputManager(inputManager) {
}

void PlayerInputManager::update(Vehicle& vehicle) {
    DrivingInputData& inputData = vehicle.getDrivingInputData();

    if (_inputManager.keyboard.isKeyPressedOrHeld(Keys::a) ||
        _inputManager.keyboard.isKeyPressedOrHeld(Keys::left)) {
        inputData.setSteeringRatio(-1.0f);
    } else if (
        _inputManager.keyboard.isKeyPressedOrHeld(Keys::d) ||
        _inputManager.keyboard.isKeyPressedOrHeld(Keys::right)) {
        inputData.setSteeringRatio(1.0f);
    } else {
        inputData.setSteeringRatio(0.0f);
    }

    if (_inputManager.keyboard.isKeyPressedOrHeld(Keys::w)) {
        float throttleRatio = getOptimalThrottleRatio(vehicle);
        inputData.setThrottleRatio(throttleRatio);
    } else if (_inputManager.keyboard.isKeyPressedOrHeld(Keys::r)) {
        inputData.setThrottleRatio(1.0f);
    } else if (_inputManager.keyboard.isKeyUnpressed(Keys::w) && _inputManager.keyboard.isKeyUnpressed(Keys::r)) {
        inputData.setThrottleRatio(0.0f);
    }

    // debug only
    if (_inputManager.keyboard.isKeyPressed(Keys::e)) {
        inputData.addThrottleRatio(0.1f);
    } else if (_inputManager.keyboard.isKeyPressed(Keys::q)) {
        inputData.addThrottleRatio(-0.1f);
    }
    // debug only

    if (_inputManager.keyboard.isKeyPressedOrHeld(Keys::s)) {
        float brakeRatio = getOptimalBrakeRatio(vehicle);
        inputData.setBrakeRatio(brakeRatio);
    } else {
        inputData.setBrakeRatio(0.0f);
    }

    inputData.resetShifting();
    if (_inputManager.keyboard.isKeyPressed(Keys::up)) {
        inputData.shiftUp();
    } else if (_inputManager.keyboard.isKeyPressed(Keys::down)) {
        inputData.shiftDown();
    }

    const float dt = CommonConstants::deltaTimeSec;
    inputData.update(dt);
}

float PlayerInputManager::getOptimalThrottleRatio(Vehicle& vehicle) {
    float throttleRatio = vehicle.getDrivingInputData().getThrottleRatio();
    VehicleData& data = vehicle.getData();
    float slipRatio = vehicle.getDriveWheel(0).getSlipRatio().value;
    if (slipRatio < 0.0f) {
        throttleRatio += 0.05f;
    } else if (slipRatio < data.optimalSlipRatioFrom) {
        throttleRatio += 0.05f;
    } else if (slipRatio > data.optimalSlipRatioTo) {
        throttleRatio -= 0.05f;
    }
    throttleRatio = Numeric::clamp(throttleRatio, 0.0f, 1.0f);

    return throttleRatio;
}

float PlayerInputManager::getOptimalBrakeRatio(Vehicle& vehicle) {
    float brakeRatio = vehicle.getDrivingInputData().getBrakeRatio();
    VehicleData& data = vehicle.getData();
    float slipRatio = Math::abs(vehicle.getDriveWheel(0).getSlipRatio().value);
    if (slipRatio < data.optimalSlipRatioFrom) {
        brakeRatio += 0.05f;
    } else if (slipRatio > data.optimalSlipRatioTo) {
        brakeRatio -= 0.05f;
    }
    brakeRatio = Numeric::clamp(brakeRatio, 0.0f, 1.0f);

    return brakeRatio;
}
