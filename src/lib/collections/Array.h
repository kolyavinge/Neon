#pragma once

#include <lib/Memory.h>
#include <lib/collections/Collection.h>
#include <lib/exceptions.h>

template<class T, int Count>
class Array : public Collection<T> {

    T _items[Count] = {};

public:
    Array<T, Count>& operator=(const Array<T, Count>& other) {
        Memory::copy<T>(other._items, _items, Count);
        return *this;
    }

    T& operator[](int index) override {
        checkBounds(index);
        return _items[index];
    }

    int getCount() const override {
        return Count;
    }

    void fillZero() {
        Memory::zero<T>(_items, Count);
    }

    void copyFrom(T* range, int count) {
        if (Count < count) throw ArgumentException(L"count must be greater or equal than source array count.");
        Memory::copy<T>(range, _items, count);
    }

    T* getItemsPointer() {
        return _items;
    }

private:
    void checkBounds(int index) {
        bool inBounds = 0 <= index && index < Count;
        if (!inBounds) throw IndexOutOfBoundsException();
    }
};
