#pragma once

#include <lib/di/InstanceCollection.h>
#include <lib/system.h>
#include <typeinfo>

class ResolveException : public Exception {

public:
    ResolveException() {}
    ResolveException(const wchar_t* msg) : Exception(msg) {}
};

class Resolver : public Object {

    InstanceCollection& _instances;
    Dictionary<unsigned int, const type_info*> _resolved;

public:
    Resolver(InstanceCollection& instances) :
        _instances(instances) {
    }

    template<class TInstance>
    TInstance& resolve() {
        const type_info& type = typeid(TInstance);
        if (!_instances.containsType(type)) throw ResolveException(L"cannot find type");
        unsigned int key = _instances.getTypeHashKey(type);
        if (!_resolved.containsKey(key)) _resolved.add(key, &type);
        TInstance* instance = (TInstance*)_instances[type]->getInstance(*this);

        return (TInstance&)*instance;
    }

    void getResolvedTypeHashKeys(List<unsigned int>& typeHashKeys) {
        _resolved.getAllKeys(typeHashKeys);
    }
};
