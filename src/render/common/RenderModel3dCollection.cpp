#include <model/common/common.h>
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
    tmpModel.setMaterial(Material::standardWithoutSpecular);
    tmpModel.moveToCenter();
    tmpModel.scale(1.25f);
    _renderModel3dLoader.load(tmpModel, output _vehicleBody);
    tmpModel.clear();

    // front wheels
    VehicleData data;
    modelPath = models3dDirectory;
    modelPath.append("vehicle_front_left_wheel.obj");
    _model3dLoader.load(modelPath, output tmpModel);
    tmpModel.setMaterial(Material::standardWithoutSpecular);
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
    tmpModel.setMaterial(Material::standardWithoutSpecular);
    tmpModel.moveToCenter();
    wheelRadius = getWheelRadius(tmpModel);
    tmpModel.scale(data.rearWheelRadius / wheelRadius);
    _renderModel3dLoader.load(tmpModel, output _vehicleWheels[(int)WheelPosition::rearLeft]);
    tmpModel.rotateByUpAxis180();
    _renderModel3dLoader.load(tmpModel, output _vehicleWheels[(int)WheelPosition::rearRight]);
    tmpModel.clear();

    // world objects
    for (int kindIndex = 0; kindIndex < (int)WorldObjectKind::_count; kindIndex++) {
        WorldObjectKind kind = (WorldObjectKind)kindIndex;
        for (int stateIndex = 0; stateIndex < (int)VisibilityState::_count; stateIndex++) {
            VisibilityState state = (VisibilityState)stateIndex;
            modelPath = models3dDirectory;
            modelPath.append(getModelNameFrom(kind, state));
            _model3dLoader.load(modelPath, output tmpModel);
            tmpModel.setMaterial(Material::standardWithoutSpecular);
            transformModel(kind, tmpModel);
            _renderModel3dLoader.load(tmpModel, output _worldObjects[(int)kind][(int)state]);
            tmpModel.clear();
        }
    }
}

String RenderModel3dCollection::getModelNameFrom(WorldObjectKind kind, VisibilityState state) {
    String name;

    if (kind == WorldObjectKind::metalFence1) name = "metal_fence_1_";
    else if (kind == WorldObjectKind::streetLight1) name = "street_light_1_";
    else throw WrongWorldObjectKindException();

    if (state == VisibilityState::high) name.append("high.obj");
    else if (state == VisibilityState::medium) name.append("medium.obj");
    else if (state == VisibilityState::low) name.append("low.obj");
    else if (state == VisibilityState::shape) name.append("shape.obj");
    else throw ArgumentException(L"Wrong state.");

    return name;
}

void RenderModel3dCollection::transformModel(WorldObjectKind kind, Model3d& model) {
    if (kind == WorldObjectKind::metalFence1) {
        model.moveToCenter();
        Measures measures = model.getMeasures();
        model.scale(WorldObjectData::getFenceLengthFor(kind) / measures.yLength);
    } else if (kind == WorldObjectKind::streetLight1) {
        Measures measures = model.getMeasures();
        model.scale(WorldObjectData::getHightFor(kind) / measures.zLength);
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

RenderModel3d& RenderModel3dCollection::getWorldObjectModel(WorldObjectKind kind, VisibilityState state) {
    return _worldObjects[(int)kind][(int)state];
}
