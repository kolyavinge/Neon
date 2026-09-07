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
    Mesh(const Mesh&) = delete; // запрещаем копирование - большой тяжелый класс
    Mesh& operator=(const Mesh&) = delete;
};

class Model3d : public Object {

    Array<Mesh, 12> _meshes;
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

private:
    Vector3 getMinVertex();
    Vector3 getMaxVertex();
};
