#include <model/world/WorldPrimitive.h>
#include <render/common/Model3dConverter.h>

void Model3dConverter::makeFromWorldSegment(WorldSegment& worldSegment, output Model3d& model3d) {
    Collection<WorldPrimitive*>& groundPrimitives = worldSegment.getGroundPrimitives();
    Mesh& mesh = model3d.createNewMesh();
    mesh.prepareEnoughCapacity(groundPrimitives.getCount(), WorldPrimitive::pointsCount);
    for (int primitiveIndex = 0; primitiveIndex < groundPrimitives.getCount(); primitiveIndex++) {
        WorldPrimitive& primitive = *groundPrimitives[primitiveIndex];
        for (int pointIndex = 0; pointIndex < WorldPrimitive::pointsCount; pointIndex++) {
            mesh.addVertex(primitive.getPoints()[pointIndex]);
            mesh.addNormal(primitive.getFrontNormal());
            mesh.addColor(0.1f, 0.4f, 0.1f, 1.0f);
            mesh.addTexCoord(primitive.getTexCoords()[pointIndex]);
        }
        mesh.addFacesForElement(primitiveIndex, WorldPrimitive::pointsCount);
    }
    //mesh.texture;
}
