#pragma once

#include <lib/di/Binder.h>
#include <lib/di/InjectModule.h>

class RenderInjectModule : public InjectModule {

public:
    void init(Binder& binder) override;
};
