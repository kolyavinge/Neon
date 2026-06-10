#pragma once

#include <concepts>
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
        // если T простой тип - инициализируем память нулями
        // если обьект - инициализировать нулями нельзя, ибо мы перезапишем vptr
        if (std::is_scalar_v<T>) {
            memset(newSource, 0, newItemsCount * sizeof(T));
        }
        if (currentItemsCount > 0) {
            copy<T>(source, newSource, currentItemsCount);
            delete[] source;
        }
        source = newSource;
    }
};
