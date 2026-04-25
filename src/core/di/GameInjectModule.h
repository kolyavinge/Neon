#pragma once

#include <lib/di/Binder.h>
#include <lib/di/InjectModule.h>

class GameInjectModule : public InjectModule {

public:
    void init(Binder& binder) override;
};
