#pragma once

#include <lib/di/DependencyContainer.h>
#include <lib/system.h>

class MainDependencyContainer : public Object {

    DependencyContainer _dependencyContainer;

public:
    MainDependencyContainer();

    template<class TInstance>
    TInstance& resolve() {
        return _dependencyContainer.resolve<TInstance>();
    }
};
