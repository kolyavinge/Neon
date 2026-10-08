#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector2.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <render/lib/Texture.h>

class Mesh : public Object {

public:
    String name; // TODO неверное не нужно
    List<float> vertices;
    List<float> normals;
    List<float> colors;
    List<float> texCoords;
    List<unsigned int> faces;
    Texture* texture;

    Mesh();
    void prepareEnoughCapacity(int elementsCount, int pointsByElement);
    void addVertex(Vector3 v);
    void addNormal(Vector3 n);
    void addColor(float r, float g, float b, float a);
    void addTexCoord(Vector2 t);
    void addFacesForElement(int elementIndex, int pointsByElement);
    void clear();
    void applyTransformMatrix4(TransformMatrix4& m);
    void merge(Mesh& mesh);
};

class Model3d : public Object {

    List<Mesh> _meshes;
    // текстуры хранятся как указатели, чтобы их проще было передать в RenderModel3d
    // и не вызывать их деструкторы в этом классе
    List<Texture*> _textures;

public:
    enum class Axis {
        x = 1,
        y = 2,
        z = 4
    };

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
    void applyTransformMatrix4(TransformMatrix4& m);
    void merge(Model3d& model3d);

private:
    Vector3 getMinVertex();
    Vector3 getMaxVertex();
};
