#pragma once

#include <lib/system.h>
#include <render/lib/VAO.h>

class VAORenderer : public Object {

public:
    void render(VAO& vao);
};
