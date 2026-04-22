#pragma once

#include <lib/di/InstanceHolder.h>

template<class TInstance>
class SimpleInstanceHolder : public InstanceHolder {

public:
    Object* getInstance(Resolver&) {
        return new TInstance();
    }
};
