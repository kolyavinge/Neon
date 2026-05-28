#include <core/di/RenderInjectModule.h>
#include <render/RenderInitializer.h>
#include <render/common/RenderModel3dCollection.h>
#include <render/common/ShaderCollection.h>
#include <render/common/ShaderProgramCollection.h>
#include <render/lib/ShaderCompiler.h>
#include <render/lib/TextureLoader.h>
#include <render/lib/model3d/Model3dLoader.h>
#include <render/lib/model3d/Model3dVAOBuilder.h>
#include <render/lib/model3d/RenderModel3dLoader.h>
#include <render/lib/vao/VAORenderer.h>
#include <render/ui/DebugScreenRenderer.h>

void RenderInjectModule::init(Binder& binder) {
    binder.bindSingleton<RenderInitializer>();
    binder.bindSingleton<RenderModel3dCollection>(RenderModel3dCollection::resolve);
    binder.bindSingleton<ShaderCollection>(ShaderCollection::resolve);
    binder.bindSingleton<ShaderProgramCollection>(ShaderProgramCollection::resolve);
    binder.bindSingleton<ShaderCompiler>(ShaderCompiler::resolve);
    binder.bindSingleton<TextureLoader>(TextureLoader::resolve);
    binder.bindSingleton<Model3dLoader>(Model3dLoader::resolve);
    binder.bindSingleton<Model3dVAOBuilder>();
    binder.bindSingleton<RenderModel3dLoader>(RenderModel3dLoader::resolve);
    binder.bindSingleton<VAORenderer>();
    binder.bindSingleton<DebugScreenRenderer>();
}
