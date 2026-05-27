#pragma once

#include <lib/system.h>
#include <render/lib/vao/VAO.h>

class VAORenderer : public Object {

public:
    void render(VAO& vao);
};
