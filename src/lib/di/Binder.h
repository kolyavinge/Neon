#pragma once

#include <lib/di/FunctionInstanceHolder.h>
#include <lib/di/InstanceCollection.h>
#include <lib/di/SimpleInstanceHolder.h>
#include <lib/di/SingletonInstanceHolder.h>
#include <lib/system.h>

class BindException : public Exception {

public:
    BindException() {}
    BindException(const wchar_t* msg) : Exception(msg) {}
};

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
            throw BindException(L"Type has been binded.");
        }
    }

    template<class TInstance>
    void bindSingleton() {
        if (!_instances.containsType(typeid(TInstance))) {
            _instances.add(typeid(TInstance), new SingletonInstanceHolder(new SimpleInstanceHolder<TInstance>()));
        } else {
            throw BindException(L"Type has been binded.");
        }
    }
};
