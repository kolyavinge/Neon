#pragma once

#include <lib/system.h>

class UniformArray : public Object {

    List<char*> _names;

public:
    void init(int itemsCount, const char *arrayName, const char *structParam);
    const char* getNameFor(int index);
};
