#include <core/di/EngineInjectModule.h>
#include <core/di/MainDependencyContainer.h>

MainDependencyContainer::MainDependencyContainer() {
    EngineInjectModule engineInjectModule;

    _dependencyContainer.initFromModule(engineInjectModule);
}
