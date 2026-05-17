#include <core/di/RenderInjectModule.h>
#include <render/RenderInitializer.h>
#include <render/common/ShaderCollection.h>
#include <render/common/ShaderProgramCollection.h>
#include <render/lib/ShaderCompiler.h>
#include <render/ui/DebugScreenRenderer.h>

void RenderInjectModule::init(Binder& binder) {
    binder.bindSingleton<RenderInitializer>();
    binder.bindSingleton<ShaderCollection>(ShaderCollection::resolve);
    binder.bindSingleton<ShaderProgramCollection>(ShaderProgramCollection::resolve);
    binder.bindSingleton<ShaderCompiler>(ShaderCompiler::resolve);
    binder.bindSingleton<DebugScreenRenderer>();
}
