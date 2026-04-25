#pragma once

#include <core/Game.h>
#include <lib/system.h>

class GameFactory : public Object {

public:
    static Game& make();
};
