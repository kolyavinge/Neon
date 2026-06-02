#pragma once

#include <lib/system.h>
#include <render/lib/Model3d.h>
#include <render/lib/VAO.h>

class Model3dVAOBuilder : public Object {

public:
    void build(Mesh& mesh, output VAO& vao);
};
