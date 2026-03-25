#pragma once

#include <lib/Object.h>
#include <lib/collections/List.h>
#include <lib/collections/LookupTable.h>

template<class T>
class Set : public Object {

    class Entry : public Object {

    public:
        T key = {};
        Entry* next = nullptr;
        bool isUsed = false;
    };

    LookupTable<T, Entry> _lookupTable;

public:
    Set(int capacity = 1000) :
        _lookupTable(capacity) {
    }

    bool add(T item) {
        unsigned int hashKey = _lookupTable.getHashKey(item);
        Entry* entry = _lookupTable.findEntryOrNull(item, hashKey);
        if (entry == nullptr) {
            _lookupTable.addEntry(item, hashKey);
            return true;
        } else {
            return false;
        }
    }

    void remove(T item) {
        unsigned int hashKey = _lookupTable.getHashKey(item);
        Entry* entry = _lookupTable.findEntryOrNull(item, hashKey);
        if (entry != nullptr) {
            entry->isUsed = false;
        }
    }

    bool contains(T item) {
        unsigned int hashKey = _lookupTable.getHashKey(item);
        Entry* entry = _lookupTable.findEntryOrNull(item, hashKey);

        return entry != nullptr;
    }

    void getAllItems(List<T>& items) {
        items.prepareEnoughCapacity(_lookupTable.getCapacity());
        for (int i = 0; i < _lookupTable.getCapacity(); i++) {
            Entry* entry = &_lookupTable.getEntry(i);
            while (entry != nullptr) {
                if (entry->isUsed) {
                    items.add(entry->key);
                }
                entry = entry->next;
            }
        }
    }

    void clear() {
        _lookupTable.clear();
    }
};
