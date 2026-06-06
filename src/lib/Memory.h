#pragma once

#include <lib/exceptions.h>
#include <string.h>

class MemoryAllocationException : public Exception {};

class Memory {

public:
    template<class T>
    static void zero(T* source, int itemsCount) {
        if (itemsCount <= 0) throw ArgumentException(L"itemsCount must be greater than zero.");
        memset(source, 0, itemsCount * sizeof(T));
    }

    template<class T>
    static void copy(const T* source, T* dest, int itemsCount) {
        if (itemsCount < 0) throw ArgumentException(L"itemsCount must be greater than zero.");
        memcpy(dest, source, itemsCount * sizeof(T));
    }

    template<class T>
    static void resize(T*& source, int currentItemsCount, int newItemsCount) {
        T* newSource = new T[(size_t)newItemsCount];
        // _items нельзя инициализировать нулями, ибо в случае с обьектами мы перезапишем vptr
        if (currentItemsCount > 0) {
            copy<T>(source, newSource, currentItemsCount);
            delete[] source;
        }
        source = newSource;
    }
};
