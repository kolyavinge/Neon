#pragma once

#include <lib/system.h>
#include <render/lib/model3d/Model3d.h>
#include <render/lib/vao/VAO.h>

class Model3dVAOBuilder : public Object {

public:
    void build(Model3d& model3d, output List<VAO>& meshVAOList);
};
