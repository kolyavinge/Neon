#pragma once

#include <lib/Object.h>
#include <lib/collections/List.h>
#include <lib/collections/LookupTable.h>
#include <lib/exceptions.h>

class KeyNotFoundException : public Exception {};
class KeyAlreadyExistException : public Exception {};

template<class TKey, class TValue>
class Dictionary : public Object {

    class Entry : public Object {

    public:
        TKey key = {};
        TValue value = {};
        Entry* next = nullptr;
        bool isUsed = false;
    };

    LookupTable<TKey, Entry> _lookupTable;

public:
    Dictionary(int capacity = 1000) :
        _lookupTable(capacity) {
    }

    void add(TKey key, TValue value) {
        unsigned int hashKey = _lookupTable.getHashKey(key);
        Entry* entry = _lookupTable.findEntryOrNull(key, hashKey);
        if (entry == nullptr) {
            entry = _lookupTable.addEntry(key, hashKey);
            entry->value = value;
        } else {
            throw KeyAlreadyExistException();
        }
    }

    void remove(TKey key) {
        unsigned int hashKey = _lookupTable.getHashKey(key);
        Entry* entry = _lookupTable.findEntryOrNull(key, hashKey);
        if (entry != nullptr) {
            entry->isUsed = false;
        } else {
            throw KeyNotFoundException();
        }
    }

    bool containsKey(TKey key) {
        unsigned int hashKey = _lookupTable.getHashKey(key);
        Entry* entry = _lookupTable.findEntryOrNull(key, hashKey);

        return entry != nullptr;
    }

    bool tryGet(TKey key, TValue*& value) {
        unsigned int hashKey = _lookupTable.getHashKey(key);
        Entry* entry = _lookupTable.findEntryOrNull(key, hashKey);
        if (entry != nullptr) {
            value = &entry->value;
            return true;
        } else {
            return false;
        }
    }

    TValue& get(TKey key) {
        TValue* value = nullptr;
        if (tryGet(key, value)) {
            return *value;
        } else {
            throw KeyNotFoundException();
        }
    }

    TValue& operator[](TKey key) {
        return get(key);
    }

    void getAllKeys(List<TKey>& keys) {
        keys.prepareEnoughCapacity(_lookupTable.getCapacity());
        for (int i = 0; i < _lookupTable.getCapacity(); i++) {
            Entry* entry = &_lookupTable.getEntry(i);
            while (entry != nullptr) {
                if (entry->isUsed) {
                    keys.add(entry->key);
                }
                entry = entry->next;
            }
        }
    }

    void getAllValues(List<TValue>& values) {
        values.prepareEnoughCapacity(_lookupTable.getCapacity());
        for (int i = 0; i < _lookupTable.getCapacity(); i++) {
            Entry* entry = &_lookupTable.getEntry(i);
            while (entry != nullptr) {
                if (entry->isUsed) {
                    values.add(entry->value);
                }
                entry = entry->next;
            }
        }
    }

    void clear() {
        _lookupTable.clear();
    }
};
