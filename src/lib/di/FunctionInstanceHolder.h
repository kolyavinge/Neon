#pragma once

#include <lib/di/InstanceHolder.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>

template<class TInstance>
using ResolvingFunction = TInstance * (*)(Resolver&);

template<class TInstance>
class FunctionInstanceHolder : public InstanceHolder {

    ResolvingFunction<TInstance> _func;

public:
    FunctionInstanceHolder(ResolvingFunction<TInstance> func) {
        _func = func;
    }

    Object* getInstance(Resolver& resolver) override {
        Object* instance = (Object*)_func(resolver);
        Assert::isFalse(instance == nullptr);

        return instance;
    }
};
