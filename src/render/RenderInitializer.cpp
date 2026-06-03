#include <render/RenderInitializer.h>

RenderInitializer::RenderInitializer(
    ShaderCollection& shaderCollection,
    ShaderProgramCollection& shaderProgramCollection,
    RenderModel3dCollection& renderModel3dCollection,
    VehicleRenderer& vehicleRenderer) :
    _shaderCollection(shaderCollection),
    _shaderProgramCollection(shaderProgramCollection),
    _renderModel3dCollection(renderModel3dCollection),
    _vehicleRenderer(vehicleRenderer) {
}

void RenderInitializer::init() {
    _shaderCollection.loadAllShaders();
    _shaderProgramCollection.initAllPrograms();
    _renderModel3dCollection.loadAllModels();
    _vehicleRenderer.init(_renderModel3dCollection);
}
