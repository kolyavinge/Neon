#include <core/di/CommonInjectModule.h>
#include <core/di/EngineInjectModule.h>
#include <core/di/MainDependencyContainer.h>

MainDependencyContainer::MainDependencyContainer() {
    _dependencyContainer.initFrom<CommonInjectModule>();
    _dependencyContainer.initFrom<EngineInjectModule>();
}
