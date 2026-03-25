#pragma once

#include <lib/system.h>

class Resolver;

class InstanceHolder : public Object {

public:
    virtual Object* getInstance(Resolver& resolver) = 0;
};
