#pragma once

#include <lib/system.h>
#include <render/lib/Material.h>
#include <render/lib/Texture.h>
#include <render/lib/vao/VAO.h>

class RenderMesh : public Object {

public:
    String name;
    VAO vao;
    Texture* texture;
    Material material;

    RenderMesh();
};

class RenderModel3d : public Object {

    List<RenderMesh> _meshes;

public:
    RenderModel3d();
    void prepareEnoughCapacityForMeshes(int meshesCount);
    RenderMesh& createNewMesh();
    Collection<RenderMesh>& getMeshes();
};
