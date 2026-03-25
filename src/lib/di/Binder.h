#pragma once

#include <lib/di/FunctionInstanceHolder.h>
#include <lib/di/InstanceCollection.h>
#include <lib/di/SingletonInstanceHolder.h>
#include <lib/system.h>

class BindException : public Exception {};

class Binder : public Object {

    InstanceCollection& _instances;

public:
    Binder(InstanceCollection& instances) :
        _instances(instances) {
    }

    template<class TInstance>
    void bindSingleton(ResolvingFunction<TInstance> func) {
        if (!_instances.containsType(typeid(TInstance))) {
            _instances.add(typeid(TInstance), new SingletonInstanceHolder(new FunctionInstanceHolder<TInstance>(func)));
        } else {
            throw BindException();
        }
    }
};
