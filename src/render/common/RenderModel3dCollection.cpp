#include <model/vehicle/VehicleData.h>
#include <render/common/RenderModel3dCollection.h>

RenderModel3dCollection::RenderModel3dCollection(
    AssetsDirectory& assetsDirectory,
    Model3dLoader& model3dLoader,
    RenderModel3dLoader& renderModel3dLoader) :
    _assetsDirectory(assetsDirectory),
    _model3dLoader(model3dLoader),
    _renderModel3dLoader(renderModel3dLoader) {
}

void RenderModel3dCollection::loadAllModels() {
    String models3dDirectory = _assetsDirectory.getModels3d();

    Model3d tmpModel;

    // vehicle body
    String modelPath = models3dDirectory;
    modelPath.append("vehicle_body.obj");
    _model3dLoader.load(modelPath, output tmpModel);
    tmpModel.moveToCenter();
    tmpModel.scale(1.25f);
    _renderModel3dLoader.load(tmpModel, output _vehicleBody);
    tmpModel.clear();

    // front wheels
    VehicleData data;
    modelPath = models3dDirectory;
    modelPath.append("vehicle_front_left_wheel.obj");
    _model3dLoader.load(modelPath, output tmpModel);
    tmpModel.moveToCenter();
    float wheelRadius = getWheelRadius(tmpModel);
    tmpModel.scale(data.frontWheelRadius / wheelRadius);
    _renderModel3dLoader.load(tmpModel, output _vehicleWheels[(int)WheelPosition::frontLeft]);
    tmpModel.rotateByUpAxis180();
    _renderModel3dLoader.load(tmpModel, output _vehicleWheels[(int)WheelPosition::frontRight]);
    tmpModel.clear();

    // rear wheels
    modelPath = models3dDirectory;
    modelPath.append("vehicle_rear_left_wheel.obj");
    _model3dLoader.load(modelPath, output tmpModel);
    tmpModel.moveToCenter();
    wheelRadius = getWheelRadius(tmpModel);
    tmpModel.scale(data.rearWheelRadius / wheelRadius);
    _renderModel3dLoader.load(tmpModel, output _vehicleWheels[(int)WheelPosition::rearLeft]);
    tmpModel.rotateByUpAxis180();
    _renderModel3dLoader.load(tmpModel, output _vehicleWheels[(int)WheelPosition::rearRight]);
    tmpModel.clear();

    // world objects
    for (int i = 0; i < _worldObjects.getCount(); i++) {
        WorldObjectKind kind = (WorldObjectKind)i;
        modelPath = models3dDirectory;
        modelPath.append(getModelNameFrom(kind));
        _model3dLoader.load(modelPath, output tmpModel);
        tmpModel.moveToCenter();
        scaleIfNeed(kind, tmpModel);
        _renderModel3dLoader.load(tmpModel, output _worldObjects[(int)kind]);
        tmpModel.clear();
    }
}

String RenderModel3dCollection::getModelNameFrom(WorldObjectKind kind) {
    switch (kind) {
        case WorldObjectKind::metalFence1: return String("metal_fence_1_high.obj");
        case WorldObjectKind::_count:
        default: throw ArgumentException(L"Wrong kind to load a 3d model.");
    }
}

void RenderModel3dCollection::scaleIfNeed(WorldObjectKind kind, Model3d& model) {
    if (kind == WorldObjectKind::metalFence1) {
        Measures measures = model.getMeasures();
        model.scale(WorldObject::getFenceLengthFor(kind) / measures.yLength);
    }
}

RenderModel3d& RenderModel3dCollection::getVehicleBody() {
    return _vehicleBody;
}

RenderModel3d& RenderModel3dCollection::getVehicleWheel(WheelPosition position) {
    return _vehicleWheels[(int)position];
}

float RenderModel3dCollection::getWheelRadius(Model3d& wheelModel) {
    // после того как колесо отцентровано, радиус - это максимальное значение по оси z (или y)
    float wheelRadius = 0.0f;
    for (int meshIndex = 0; meshIndex < wheelModel.getMeshesCount(); meshIndex++) {
        Mesh& mesh = wheelModel.getMesh(meshIndex);
        for (int vertexIndex = 2; vertexIndex < mesh.vertices.getCount(); vertexIndex += 3) {
            float z = mesh.vertices[vertexIndex];
            if (wheelRadius < z) wheelRadius = z;
        }
    }

    return wheelRadius;
}

RenderModel3d& RenderModel3dCollection::getWorldObjectModelForKind(WorldObjectKind kind) {
    return _worldObjects[(int)kind];
}
