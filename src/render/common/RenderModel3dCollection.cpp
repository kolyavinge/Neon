#include <render/common/RenderModel3dCollection.h>
#include <render/lib/model3d/Model3d.h>

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

    String vehicleModelPath = models3dDirectory;
    vehicleModelPath.append(L"vehicle\\model.fbx");
    Model3d vehicleModel;
    _model3dLoader.load(vehicleModelPath, output vehicleModel);
    vehicleModel.scale(0.5f, 0.5f, 0.5f);
    _renderModel3dLoader.load(vehicleModel, output vehicle);
}
