#pragma once

#include <lib/exceptions.h>
#include <malloc.h>
#include <string.h>

class MemoryAllocationException : public Exception {};

class Memory {

public:
    template<class T>
    static T* allocate(int itemsCount) {
        if (itemsCount <= 0) throw ArgumentException();
        T* result = (T*)malloc(itemsCount * sizeof(T));
        if (result == nullptr) throw MemoryAllocationException();
        zero<T>(result, itemsCount);

        return result;
    }

    template<class T>
    static void zero(T* source, int itemsCount) {
        if (itemsCount <= 0) throw ArgumentException();
        memset(source, 0, itemsCount * sizeof(T));
    }

    template<class T>
    static void copy(const T* source, T* dest, int itemsCount) {
        if (itemsCount < 0) throw ArgumentException();
        memcpy(dest, source, itemsCount * sizeof(T));
    }

    static void release(void* source) {
        free(source);
    }

    template<class T>
    static void resize(T*& source, int currentItemsCount, int newItemsCount) {
        T* newSource = allocate<T>(newItemsCount);
        copy<T>(source, newSource, currentItemsCount);
        release(source);
        source = newSource;
    }
};
