#pragma once

#include <concepts>
#include <lib/Assert.h>
#include <lib/exceptions.h>
#include <string.h>

class MemoryAllocationException : public Exception {};

class Memory {

public:
    template<class T>
    static void zero(T* source, int itemsCount) requires std::is_scalar_v<T> {
        if (itemsCount <= 0) throw ArgumentException(L"itemsCount must be greater than zero.");
        memset(source, 0, itemsCount * sizeof(T));
    }

    template<class T>
    static void copy(const T* source, T* dest, int itemsCount) requires std::is_scalar_v<T> {
        if (itemsCount < 0) throw ArgumentException(L"itemsCount must be greater than zero.");
        memcpy(dest, source, itemsCount * sizeof(T));
    }

    template<class T>
    _NODISCARD static T* resize(T* source, int currentItemsCount, int newItemsCount) {
        if (source == nullptr) throw ArgumentException(L"source cannot be null.");
        if (newItemsCount < currentItemsCount) throw ArgumentException(L"newItemsCount must be greater than currentItemsCount.");

        // Выделяем память без вызова конструкторов
        T* newSource = static_cast<T*>(::operator new[](newItemsCount * sizeof(T)));

        // Копируем старые элементы в новую память с помощью конструктора копирования
        // (элемент создается прямо в выделенном куске памяти)
        for (int i = 0; i < currentItemsCount; i++) {
            ::new (static_cast<void*>(newSource + i)) T(source[i]);
        }

        // Инициализируем оставшуюся память, для базовых типов - зануление, для классов — вызов конструктора
        for (int i = currentItemsCount; i < newItemsCount; i++) {
            ::new (static_cast<void*>(newSource + i)) T();
        }

        for (int i = 0; i < currentItemsCount; i++) {
            source[i].~T();
        }
        ::operator delete[](source);

        return newSource;
    }
};
