#pragma once

#include <lib/di/InjectModule.h>
#include <lib/system.h>

class EngineInjectModule : public InjectModule {

public:
    void init(Binder& binder) override;
};
