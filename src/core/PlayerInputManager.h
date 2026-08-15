#pragma once

#include <common/InputManager.h>
#include <lib/di/Resolver.h>
#include <model/vehicle/DrivingInputData.h>

class PlayerInputManager : public Object {

    InputManager& _inputManager;

public:
    static PlayerInputManager* resolve(Resolver& resolver) {
        return new PlayerInputManager(
            resolver.resolve<InputManager>());
    }

    PlayerInputManager(
        InputManager& inputManager);

    void update(DrivingInputData& inputData);
};
