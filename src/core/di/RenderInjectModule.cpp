#include <core/di/RenderInjectModule.h>
#include <render/RenderInitializer.h>
#include <render/ui/DebugScreenRenderer.h>

void RenderInjectModule::init(Binder& binder) {
    binder.bindSingleton<RenderInitializer>();
    binder.bindSingleton<DebugScreenRenderer>();
}
