#pragma once

#include <lib/system.h>
#include <lib/di/Binder.h>

class InjectModule : public Object {

public:
    virtual void init(Binder& binder) = 0;
};
