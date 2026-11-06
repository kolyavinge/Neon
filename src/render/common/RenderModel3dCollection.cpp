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
    modelPath.append("vehicle_body.obj");
    Model3d vehicleBodyModel;
    _model3dLoader.load(modelPath, output vehicleBodyModel);
    vehicleBodyModel.moveToCenter();
    vehicleBodyModel.scale(1.25f);
    _renderModel3dLoader.load(vehicleBodyModel, output vehicleBody);

    // front wheels
    VehicleData data;
    modelPath = models3dDirectory;
    modelPath.append("vehicle_front_left_wheel.obj");
    Model3d frontLeftWheelModel;
    _model3dLoader.load(modelPath, output frontLeftWheelModel);
    frontLeftWheelModel.moveToCenter();
    float wheelRadius = getWheelRadius(frontLeftWheelModel);
    frontLeftWheelModel.scale(data.frontWheelRadius / wheelRadius);
    _renderModel3dLoader.load(frontLeftWheelModel, output vehicleFrontLeftWheel);
    frontLeftWheelModel.rotateByUpAxis180();
    _renderModel3dLoader.load(frontLeftWheelModel, output vehicleFrontRightWheel);

    // rear wheels
    modelPath = models3dDirectory;
    modelPath.append("vehicle_rear_left_wheel.obj");
    Model3d rearLeftWheelModel;
    _model3dLoader.load(modelPath, output rearLeftWheelModel);
    rearLeftWheelModel.moveToCenter();
    wheelRadius = getWheelRadius(rearLeftWheelModel);
    rearLeftWheelModel.scale(data.rearWheelRadius / wheelRadius);
    _renderModel3dLoader.load(rearLeftWheelModel, output vehicleRearLeftWheel);
    rearLeftWheelModel.rotateByUpAxis180();
    _renderModel3dLoader.load(rearLeftWheelModel, output vehicleRearRightWheel);
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
