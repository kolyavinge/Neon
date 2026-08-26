#pragma once

#include <common/InputManager.h>
#include <lib/di/Resolver.h>
#include <model/vehicle/Vehicle.h>

class PlayerInputManager : public Object {

    InputManager& _inputManager;

public:
    static PlayerInputManager* resolve(Resolver& resolver) {
        return new PlayerInputManager(
            resolver.resolve<InputManager>());
    }

    PlayerInputManager(
        InputManager& inputManager);

    void update(Vehicle& vehicle);

private:
    float getOptimalThrottleRatio(Vehicle& vehicle);
    float getOptimalBrakeRatio(Vehicle& vehicle);
};
