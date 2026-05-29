#pragma once

#include <lib/system.h>

class Environment : public Object {

public:
    String getCurrentDirectory();
};
