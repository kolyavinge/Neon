#pragma once

#include <lib/di/Resolver.h>
#include <lib/input/Keyboard.h>
#include <lib/system.h>

class InputManager : public Object {

public:
    Keyboard keyboard;

    static InputManager* resolve(Resolver&) {
        return new InputManager();
    }

    void updateDevices();
};
