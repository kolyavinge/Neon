#pragma once

#include <lib/di/Binder.h>
#include <lib/di/InjectModule.h>
#include <lib/di/InstanceCollection.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>

class DependencyContainer : public Object {

    InstanceCollection _instances;
    Resolver _resolver;
    Binder _binder;

public:
    DependencyContainer() :
        _resolver(_instances),
        _binder(_instances) {
    }

    template<class TInstance>
    TInstance& resolve() {
        return _resolver.resolve<TInstance>();
    }

    void initFromModule(InjectModule& module) {
        module.init(_binder);
    }

    String getUnusedInstancesAsString() {
        List<unsigned int> unresolvedTypeHashKeys;
        List<unsigned int> resolvedTypeHashKeys;
        _instances.getAllTypeHashKeys(unresolvedTypeHashKeys);
        _resolver.getResolvedTypeHashKeys(resolvedTypeHashKeys);
        unresolvedTypeHashKeys.removeAll(resolvedTypeHashKeys);
        String result;
        for (int i = 0; i < unresolvedTypeHashKeys.getCount(); i++) {
            String str(_instances.getTypeInfo(unresolvedTypeHashKeys[i]).name());
            result.append(str);
            result.append(L'\n');
        }

        return result;
    }
};
