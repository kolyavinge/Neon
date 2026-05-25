#pragma once

#include <lib/calc/Vector2.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <render/lib/Texture.h>

class Face : public Object {

public:
    unsigned int i0;
    unsigned int i1;
    unsigned int i2;

    Face();
};

class Mesh : public Object {

public:
    int id;
    List<Vector3> vertices;
    List<Vector3> normals;
    List<Vector2> texCoords;
    List<Face> faces;
    Texture* texture;

    Mesh();
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
