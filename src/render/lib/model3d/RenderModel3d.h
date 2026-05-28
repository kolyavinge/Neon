#pragma once

#include <lib/system.h>
#include <render/lib/Material.h>
#include <render/lib/Texture.h>
#include <render/lib/vao/VAO.h>

class RenderMesh : public Object {

    VAO _vao;
    Texture* _texture;
    Material _material;

public:
    RenderMesh();
    VAO& getVAO();
    Texture& getTexture();
    void setTexture(Texture* texture);
    Material& getMaterial();
    void setMaterial(Material& material);
};

class RenderModel3d : public Object {

    List<RenderMesh> _meshes;

public:
    RenderMesh& createNewMesh();
    Collection<RenderMesh>& getMeshes();
};
