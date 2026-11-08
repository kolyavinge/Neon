#include <render/lib/UniformArray.h>

void UniformArray::init(int itemsCount, const char* arrayName, const char* structParam) {
    for (int i = 0; i < _names.getCount(); i++) {
        delete[] _names[i];
    }
    _names.clear();
    _names.prepareEnoughCapacity(itemsCount);
    String name;
    for (int i = 0; i < itemsCount; i++) {
        name = arrayName;
        name.append('[');
        name.append(Numeric::intToString(i));
        name.append(']');
        name.append('.');
        name.append(structParam);
        _names.addNew();
        _names[i] = new char[(size_t)name.getLength()];
        name.getCharPointer(_names[i], (unsigned int)(name.getLength() + 1)); // +1 zero symb
    }
}

const char* UniformArray::getNameFor(int index) {
    return _names[index];
}
