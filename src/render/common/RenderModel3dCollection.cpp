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

    // vehicle body
    String modelPath = models3dDirectory;
    modelPath.append("vehicle_body.glb");
    Model3d vehicleBodyModel;
    _model3dLoader.load(modelPath, output vehicleBodyModel);
    vehicleBodyModel.invertAxis((int)Model3d::Axis::x | (int)Model3d::Axis::z);
    vehicleBodyModel.moveToCenter();
    vehicleBodyModel.moveToOrigin((int)Model3d::Axis::z);
    vehicleBodyModel.scale(1.25f);
    _renderModel3dLoader.load(vehicleBodyModel, output vehicleBody);

    // front wheels
    VehicleData data;
    modelPath = models3dDirectory;
    modelPath.append("vehicle_front_right_wheel.glb");
    Model3d frontWheelModel;
    _model3dLoader.load(modelPath, output frontWheelModel);
    frontWheelModel.moveToCenter();
    float wheelRadius = getWheelRadius(frontWheelModel);
    frontWheelModel.scale(data.frontWheelRadius / wheelRadius);
    _renderModel3dLoader.load(frontWheelModel, output vehicleFrontRightWheel);
    frontWheelModel.invertAxis((int)Model3d::Axis::x);
    _renderModel3dLoader.load(frontWheelModel, output vehicleFrontLeftWheel);

    // rear wheels
    modelPath = models3dDirectory;
    modelPath.append("vehicle_rear_right_wheel.glb");
    Model3d rearWheelModel;
    _model3dLoader.load(modelPath, output rearWheelModel);
    rearWheelModel.invertAxis((int)Model3d::Axis::x);
    rearWheelModel.moveToCenter();
    wheelRadius = getWheelRadius(rearWheelModel);
    rearWheelModel.scale(data.rearWheelRadius / wheelRadius);
    _renderModel3dLoader.load(rearWheelModel, output vehicleRearRightWheel);
    rearWheelModel.invertAxis((int)Model3d::Axis::x);
    _renderModel3dLoader.load(rearWheelModel, output vehicleRearLeftWheel);
}

float RenderModel3dCollection::getWheelRadius(Model3d& wheelModel) {
    // после того как колесо отцентровано, радиус - это максимальное значение по оси z (или y)
    float wheelRadius = 0.0f;
    Collection<Mesh>& meshes = wheelModel.getMeshes();
    for (int meshIndex = 0; meshIndex < meshes.getCount(); meshIndex++) {
        Mesh& mesh = meshes[meshIndex];
        for (int vertexIndex = 2; vertexIndex < mesh.vertices.getCount(); vertexIndex += 3) {
            float z = mesh.vertices[vertexIndex];
            if (wheelRadius < z) wheelRadius = z;
        }
    }

    return wheelRadius;
}
