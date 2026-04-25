#include <core/di/RenderInjectModule.h>
#include <render/ui/DebugScreenRenderer.h>

void RenderInjectModule::init(Binder& binder) {
    binder.bindSingleton<DebugScreenRenderer>();
}
