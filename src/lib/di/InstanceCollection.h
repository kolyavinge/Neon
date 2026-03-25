#pragma once

#include <lib/di/InstanceHolder.h>
#include <lib/system.h>
#include <typeinfo>

class InstanceCollection : public Object {

    Dictionary<unsigned int, InstanceHolder*> _instances;
    Dictionary<unsigned int, const type_info*> _types;

public:
    ~InstanceCollection() override;

    unsigned int getTypeHashKey(const type_info& type);
    InstanceHolder*& operator[](const type_info& type);
    bool containsType(const type_info& type);
    void add(const type_info& type, InstanceHolder* instanceHolder);
    const type_info& getTypeInfo(unsigned int typeHashKey);
    void getAllTypeHashKeys(List<unsigned int>& typeHashKeys);
};
