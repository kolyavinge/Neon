#include <common/constants.h>
#include <core/PlayerInputManager.h>
#include <lib/Numeric.h>
#include <lib/calc/Math.h>
#include <model/vehicle/DrivingInputData.h>
#include <model/vehicle/VehicleData.h>
#include <model/vehicle/Wheel.h>

PlayerInputManager::PlayerInputManager(
    InputManager& inputManager) :
    _inputManager(inputManager) {
}

void PlayerInputManager::update(Vehicle& vehicle) {
    DrivingInputData& inputData = vehicle.getDrivingInputData();

    // steering
    if (_inputManager.keyboard.isKeyPressedOrHeld(Keys::a) ||
        _inputManager.keyboard.isKeyPressedOrHeld(Keys::left) ||
        _inputManager.joystick.isKeyPressedOrHeld(Keys::left)) {
        inputData.setSteeringRatio(-1.0f);
    } else if (
        _inputManager.keyboard.isKeyPressedOrHeld(Keys::d) ||
        _inputManager.keyboard.isKeyPressedOrHeld(Keys::right) ||
        _inputManager.joystick.isKeyPressedOrHeld(Keys::right)) {
        inputData.setSteeringRatio(1.0f);
    } else {
        inputData.setSteeringRatio(0.0f);
    }

    // throttle
    if (_inputManager.keyboard.isKeyPressedOrHeld(Keys::w) ||
        _inputManager.joystick.isKeyPressedOrHeld(Keys::button3)) {
        //float throttleRatio = getOptimalThrottleRatio(vehicle); // TODO пока алгоритм нормально не работает
        float throttleRatio = 1.0f;
        inputData.setThrottleRatio(throttleRatio);
    } else if (
        _inputManager.keyboard.isKeyPressedOrHeld(Keys::r) ||
        _inputManager.joystick.isKeyPressedOrHeld(Keys::button2)) {
        inputData.setThrottleRatio(1.0f);
    } else if (_inputManager.keyboard.isKeyUnpressed(Keys::w) && _inputManager.keyboard.isKeyUnpressed(Keys::r)) {
        inputData.setThrottleRatio(0.0f);
    }

    // braking
    if (_inputManager.keyboard.isKeyPressedOrHeld(Keys::s) ||
        _inputManager.joystick.isKeyPressedOrHeld(Keys::button4)) {
        float brakeRatio = getOptimalBrakeRatio(vehicle);
        inputData.setBrakeRatio(brakeRatio);
    } else {
        inputData.setBrakeRatio(0.0f);
    }

    // gear shifting
    inputData.resetShifting();
    if (_inputManager.keyboard.isKeyPressed(Keys::up) ||
        _inputManager.joystick.isKeyPressed(Keys::button6)) {
        inputData.shiftUp();
    } else if (
        _inputManager.keyboard.isKeyPressed(Keys::down) ||
        _inputManager.joystick.isKeyPressed(Keys::button5)) {
        inputData.shiftDown();
    }

    if (_inputManager.keyboard.isKeyPressed(Keys::z)) {
        Gearbox& gearbox = vehicle.getGearbox();
        gearbox.setKind(gearbox.getKind() == GearboxKind::manual ? GearboxKind::automatic : GearboxKind::manual);
    }

    // debug only
    if (_inputManager.keyboard.isKeyPressed(Keys::e)) {
        inputData.addThrottleRatio(0.1f);
    } else if (_inputManager.keyboard.isKeyPressed(Keys::q)) {
        inputData.addThrottleRatio(-0.1f);
    }
    // debug only

    const float dt = CommonConstants::deltaTimeSec;
    inputData.update(dt);
}

float PlayerInputManager::getOptimalThrottleRatio(Vehicle& vehicle) {
    float throttleRatio = vehicle.getDrivingInputData().getThrottleRatio();
    VehicleData& data = vehicle.getData();
    float averageSlipRatio =
        (vehicle.getDriveWheel(0).getSlipRatio().value + vehicle.getDriveWheel(1).getSlipRatio().value) / (float)VehicleConstants::oneAxleWheelsCount;
    if (averageSlipRatio < data.optimalSlipRatioFrom) {
        throttleRatio += 0.1f;
    } else if (averageSlipRatio > data.optimalSlipRatioTo) {
        throttleRatio -= 0.01f;
    }
    throttleRatio = Numeric::clamp(throttleRatio, 0.2f, 1.0f);

    return throttleRatio;
}

float PlayerInputManager::getOptimalBrakeRatio(Vehicle& vehicle) {
    float brakeRatio = vehicle.getDrivingInputData().getBrakeRatio();
    VehicleData& data = vehicle.getData();
    float averageSlipRatio = 0.0f;
    for (int i = 0; i < VehicleConstants::wheelsCount; i++) {
        averageSlipRatio += Math::abs(vehicle.getWheel(i).getSlipRatio().value);
    }
    averageSlipRatio /= (float)VehicleConstants::wheelsCount;
    if (averageSlipRatio < data.optimalSlipRatioFrom) {
        brakeRatio += 0.01f;
    } else if (averageSlipRatio > data.optimalSlipRatioTo) {
        brakeRatio -= 0.01f;
    }
    brakeRatio = Numeric::clamp(brakeRatio, 0.1f, 1.0f);

    return brakeRatio;
}
