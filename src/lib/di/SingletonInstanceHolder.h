#pragma once

#include <lib/Object.h>
#include <lib/di/InstanceHolder.h>
#include <lib/di/Resolver.h>

class SingletonInstanceHolder : public InstanceHolder {

    InstanceHolder* _instanceHolder;
    Object* _instance;

public:
    SingletonInstanceHolder(InstanceHolder* instanceHolder);

    Object* getInstance(Resolver& resolver) override;
};
