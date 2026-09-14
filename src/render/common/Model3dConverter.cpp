#include <model/world/WorldPrimitive.h>
#include <render/common/Model3dConverter.h>

Model3dConverter::Model3dConverter(
    TextureCollection& textureCollection) :
    _textureCollection(textureCollection) {
}

void Model3dConverter::fromWorldSegment(WorldSegment& worldSegment, output Model3d& model3d) {
    Collection<WorldPrimitive*>& groundPrimitives = worldSegment.getGroundPrimitives();

    List<Group<WorldPrimitiveKind, WorldPrimitive**>> grouped;
    WorldPrimitiveKind(*getGroupKey)(WorldPrimitive *&pr) = [](WorldPrimitive*& pr) { return pr->getKind(); };
    groundPrimitives.groupBy(getGroupKey, output grouped);

    for (int i = 0; i < grouped.getCount(); i++) {
        Group<WorldPrimitiveKind, WorldPrimitive**>& group = grouped[i];
        Mesh& mesh = model3d.createNewMesh();
        mesh.prepareEnoughCapacity(group.getItemsCount(), WorldPrimitive::pointsCount);
        for (int primitiveIndex = 0; primitiveIndex < group.getItemsCount(); primitiveIndex++) {
            WorldPrimitive& primitive = **group[primitiveIndex];
            for (int pointIndex = 0; pointIndex < WorldPrimitive::pointsCount; pointIndex++) {
                mesh.addVertex(primitive.getPoints()[pointIndex]);
                mesh.addNormal(primitive.getFrontNormal());
                mesh.addColor(0.1f, 0.4f, 0.1f, 1.0f);
                mesh.addTexCoord(primitive.getTexCoords()[pointIndex]);
            }
            mesh.addFacesForElement(primitiveIndex, WorldPrimitive::pointsCount);
        }
        mesh.texture = &_textureCollection.getByWorldPrimitiveKind(group.getKey());
    }
}
