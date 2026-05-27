#pragma once

#include <lib/system.h>
#include <render/lib/Texture.h>

class Mesh : public Object {

public:
    int id;
    List<float> vertices;
    List<float> normals;
    List<float> texCoords;
    List<unsigned int> faces;
    Texture* texture;

    Mesh();
    void scale(float x, float y, float z);
};

class Model3d : public Object {

    List<Mesh> _meshes;
    List<Texture> _textures;

public:
    Mesh& createNewMesh();
    Collection<Mesh>& getMeshes();
    Texture& createNewTexture();
    Collection<Texture>& getTextures();
};
