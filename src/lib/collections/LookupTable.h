#pragma once

#include <lib/Hasher.h>
#include <lib/Memory.h>
#include <lib/Object.h>
#include <lib/exceptions.h>

template<class TKey, class TEntry>
class LookupTable : public Object {

    int _capacity;
    TEntry* _entries;
    Hasher<TKey> _hasher;

public:
    LookupTable(int capacity) {
        if (capacity <= 0) throw ArgumentException();
        _capacity = capacity;
        _entries = Memory::allocate<TEntry>(_capacity);
    }

    ~LookupTable() override {
        release();
    }

    int getCapacity() {
        return _capacity;
    }

    TEntry& getEntry(int index) {
        return _entries[index];
    }

    unsigned int getHashKey(TKey key) {
        return _hasher.getHash(key) % _capacity;
    }

    TEntry* addEntry(TKey key, unsigned int hashKey) {
        TEntry* entry = &_entries[hashKey];
        if (!entry->isUsed) {
            entry->key = key;
            entry->isUsed = true;
        } else {
            while (entry->isUsed && entry->next != nullptr) {
                entry = entry->next;
            }
            if (entry->isUsed) {
                TEntry* newEntry = new TEntry();
                newEntry->key = key;
                newEntry->next = nullptr;
                newEntry->isUsed = true;
                entry->next = newEntry;
                entry = newEntry;
            } else {
                entry->key = key;
                entry->isUsed = true;
            }
        }

        return entry;
    }

    TEntry* findEntryOrNull(TKey key, unsigned int hashKey) {
        TEntry* entry = &_entries[hashKey];
        while (entry != nullptr) {
            if (entry->isUsed && entry->key == key) {
                return entry;
            } else {
                entry = entry->next;
            }
        }

        return nullptr;
    }

    void clear() {
        for (int i = 0; i < _capacity; i++) {
            _entries[i].isUsed = false;
            TEntry* child = _entries[i].next;
            while (child != nullptr) {
                child->isUsed = false;
                child = child->next;
            }
        }
    }

private:
    void release() {
        for (int i = 0; i < _capacity; i++) {
            if (_entries[i].next != nullptr) {
                releaseLinkedEntries(_entries[i].next);
            }
        }
        Memory::release(_entries);
    }

    void releaseLinkedEntries(TEntry* entry) {
        if (entry->next != nullptr) {
            releaseLinkedEntries(entry->next);
        }
        delete entry;
    }
};
