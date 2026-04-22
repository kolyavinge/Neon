#pragma once

#include <lib/system.h>

class ScreenRenderer : public Object {

public:
    void virtual render() = 0;
};
