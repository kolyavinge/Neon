#include <lib/di/SingletonInstanceHolder.h>

SingletonInstanceHolder::SingletonInstanceHolder(InstanceHolder* instanceHolder) {
    _instanceHolder = instanceHolder;
    _instance = nullptr;
}

Object* SingletonInstanceHolder::getInstance(Resolver& resolver) {
    if (_instance == nullptr) {
        _instance = _instanceHolder->getInstance(resolver);
    }

    return _instance;
}
