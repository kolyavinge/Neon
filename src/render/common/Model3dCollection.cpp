#include <model/common/common.h>
#include <render/common/Model3dCollection.h>

Model3dCollection::Model3dCollection(
    AssetsDirectory& assetsDirectory,
    Model3dLoader& model3dLoader) :
    _assetsDirectory(assetsDirectory),
    _model3dLoader(model3dLoader) {
}

void Model3dCollection::unload() {
    for (int i = 0; i < _worldObjects.getCount(); i++) {
        delete _worldObjects[i];
        _worldObjects[i] = nullptr;
    }
}

Model3d& Model3dCollection::getModelFor(WorldObjectKind kind) {
    if (_worldObjects[(int)kind] == nullptr) {
        String modelDirectory = _assetsDirectory.getModels3d();
        String modelName = getModelNameFrom(kind);
        modelDirectory.append(modelName);
        Model3d* model = new Model3d();
        _model3dLoader.load(modelDirectory, output *model);
        model->moveToCenter();
        scaleIfNeed(kind, model);
        _worldObjects[(int)kind] = model;
    }

    return *_worldObjects[(int)kind];
}

void Model3dCollection::scaleIfNeed(WorldObjectKind kind, Model3d* model) {
    if (kind == WorldObjectKind::metalFence1) {
        Measures measures = model->getMeasures();
        model->scale(WorldObject::getFenceLengthFor(kind) / measures.yLength);
    }
}

String Model3dCollection::getModelNameFrom(WorldObjectKind kind) {
    switch (kind) {
        case WorldObjectKind::metalFence1: return String("metal_fence_1.obj");
        case WorldObjectKind::_count:
        default: throw ArgumentException(L"Wrong kind to load a 3d model.");
    }
}
