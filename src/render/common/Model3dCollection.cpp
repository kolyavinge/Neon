#include <render/common/Model3dCollection.h>

Model3dCollection::Model3dCollection(
    AssetsDirectory& assetsDirectory,
    Model3dLoader& model3dLoader) :
    _assetsDirectory(assetsDirectory),
    _model3dLoader(model3dLoader) {
}

void Model3dCollection::unload() {
    for (int i = 0; i < _worldPrimitives.getCount(); i++) {
        delete _worldPrimitives[i];
        _worldPrimitives[i] = nullptr;
    }
}

Model3d& Model3dCollection::getModelFor(WorldPrimitiveKind kind) {
    if (_worldPrimitives[(int)kind] == nullptr) {
        String modelDirectory = _assetsDirectory.getModels3d();
        String modelName = getModelNameFrom(kind);
        modelDirectory.append(modelName);
        Model3d* model = new Model3d();
        _model3dLoader.load(modelDirectory, output *model);
        _worldPrimitives[(int)kind] = model;
    }

    return *_worldPrimitives[(int)kind];
}

String Model3dCollection::getModelNameFrom(WorldPrimitiveKind kind) {
    switch (kind) {
        case WorldPrimitiveKind::metalBarrier1: return String("vehicle_front_right_wheel.glb");
        case WorldPrimitiveKind::asphalt1:
        case WorldPrimitiveKind::asphalt2:
        case WorldPrimitiveKind::asphalt3:
        case WorldPrimitiveKind::_count:
        default: throw ArgumentException(L"Wrong kind to load a 3d model.");
    }
}
