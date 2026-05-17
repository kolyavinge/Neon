#pragma once

#include <lib/system.h>

class ProjectDirectories : public Object {

    String _root;
    String _shaders;

public:
    ProjectDirectories();
    String& getShaders();
};
