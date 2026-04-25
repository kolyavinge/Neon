#pragma once

#include <core/InputManager.h>
#include <lib/di/Resolver.h>
#include <model/vehicle/DrivingInputData.h>

class DrivingInputManager : public Object {

    InputManager& _inputManager;

public:
    static DrivingInputManager* resolve(Resolver& resolver) {
        return new DrivingInputManager(
            resolver.resolve<InputManager>());
    }

    DrivingInputManager(
        InputManager& inputManager);

    void update(DrivingInputData& inputData);
};
