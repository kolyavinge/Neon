#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <render/lib/Texture.h>

class Mesh : public Object {

public:
    int id;
    String name;
    List<float> vertices;
    List<float> normals;
    List<float> colors;
    List<float> texCoords;
    List<unsigned int> faces;
    Texture* texture;

    Mesh();
};

class Model3d : public Object {

    List<Mesh> _meshes;
    List<Texture> _textures;

public:
    enum class Axis {
        x = 1,
        y = 2,
        z = 4
    };

    void prepareEnoughCapacityForMeshes(int meshesCount);
    Mesh& createNewMesh();
    Collection<Mesh>& getMeshes();
    Texture& createNewTexture();
    Collection<Texture>& getTextures();
    void moveToOrigin();
    void moveToCenter(int axis);
    void scale(float scale);
    void invertAxis(int axis);

private:
    Vector3 getMinVertex();
    Vector3 getMaxVertex();
};
