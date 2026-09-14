#pragma once

#include <lib/calc/Vector2.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <render/lib/Texture.h>

class Mesh : public Object {

public:
    String name;
    List<float> vertices;
    List<float> normals;
    List<float> colors;
    List<float> texCoords;
    List<unsigned int> faces;
    Texture* texture;

    DENY_COPYING(Mesh); // потому что большой тяжелый класс
    Mesh();
    void prepareEnoughCapacity(int elementsCount, int pointsByElement);
    void addVertex(Vector3 v);
    void addNormal(Vector3 n);
    void addColor(float r, float g, float b, float a);
    void addTexCoord(Vector2 t);
    void addFacesForElement(int elementIndex, int pointsByElement);
    void clear();
};

class Model3d : public Object {

    Array<Mesh, 20> _meshes;
    int _meshesCount;
    // текстуры хранятся как указатели, чтобы их проще было передать в RenderModel3d
    // и не вызывать деструктор в этом классе
    List<Texture*> _textures;

public:
    enum class Axis {
        x = 1,
        y = 2,
        z = 4
    };

    Model3d();
    Mesh& createNewMesh();
    Mesh& getMesh(int index);
    int getMeshesCount();
    Texture& createNewTexture();
    Texture& getTexture(int index);
    Collection<Texture*>& getTextures();
    int getTexturesCount();
    void moveToOrigin(int axis = 0);
    void moveToCenter(int axis = 0);
    void scale(float scale);
    void invertAxis(int axis);
    void clear();

private:
    Vector3 getMinVertex();
    Vector3 getMaxVertex();
};
