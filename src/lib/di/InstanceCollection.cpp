#include <lib/di/InstanceCollection.h>
#include <lib/system.h>

InstanceCollection::~InstanceCollection() {
    List<InstanceHolder*> allInstances;
    _instances.getAllValues(allInstances);
    for (int i = 0; i < allInstances.getCount(); i++) {
        delete allInstances[i];
    }
}

unsigned int InstanceCollection::getTypeHashKey(const type_info& type) {
    return (unsigned int)type.hash_code();
}

InstanceHolder*& InstanceCollection::operator[](const type_info& type) {
    unsigned int key = getTypeHashKey(type);
    return _instances[key];
}

bool InstanceCollection::containsType(const type_info& type) {
    unsigned int key = getTypeHashKey(type);
    return _instances.containsKey(key);
}

void InstanceCollection::add(const type_info& type, InstanceHolder* instanceHolder) {
    unsigned int key = getTypeHashKey(type);
    _instances.add(key, instanceHolder);
    _types.add(key, &type);
}

const type_info& InstanceCollection::getTypeInfo(unsigned int typeHashKey) {
    return *_types[typeHashKey];
}

void InstanceCollection::getAllTypeHashKeys(List<unsigned int>& typeHashKeys) {
    _types.getAllKeys(typeHashKeys);
}
