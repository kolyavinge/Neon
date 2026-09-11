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

    List<RenderMesh*> _meshes;
    List<Texture*> _textures;

public:
    ~RenderModel3d();
    RenderModel3d& operator=(const RenderModel3d& other);
    RenderMesh& createNewMesh();
    RenderMesh& getMesh(int index);
    int getMeshesCount();
    RenderMesh& getMeshByName(String meshName);
    void setTextures(Collection<Texture*>& textures);
    void release();
};
