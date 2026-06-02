#pragma once

#include <lib/system.h>
#include <render/lib/Texture.h>

class Mesh : public Object {

public:
    int id;
    String name;
    List<float> vertices;
    List<float> normals;
    List<float> texCoords;
    List<unsigned int> faces;
    Texture* texture;

    Mesh();
};

class Model3d : public Object {

    List<Mesh> _meshes;
    List<Texture> _textures;

public:
    void prepareEnoughCapacityForMeshes(int meshesCount);
    Mesh& createNewMesh();
    Collection<Mesh>& getMeshes();
    Texture& createNewTexture();
    Collection<Texture>& getTextures();
    void scale(float x, float y, float z);
};
