#pragma once

#include <lib/system.h>
#include <render/lib/Material.h>
#include <render/lib/Texture.h>
#include <render/lib/VAO.h>

class RenderMesh : public Object {

public:
    String name;
    VAO vao;
    Texture* texture;
    Material material;

    RenderMesh();
};

class RenderModel3d : public Object {

    Array<RenderMesh, 20> _meshes;
    int _meshesCount;

public:
    RenderModel3d();
    RenderMesh& createNewMesh();
    RenderMesh& getMesh(int index);
    int getMeshesCount();
    RenderMesh& getMeshByName(String meshName);
};
