#include <render/common/RenderModel3dCollection.h>
#include <render/lib/Model3d.h>

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
    vehicleBodyModel.scale(1.25f);
    vehicleBodyModel.invertAxis((int)Model3d::Axis::x | (int)Model3d::Axis::z);
    vehicleBodyModel.moveToCenter((int)Model3d::Axis::x | (int)Model3d::Axis::y | (int)Model3d::Axis::z);
    _renderModel3dLoader.load(vehicleBodyModel, output vehicleBody);
}
