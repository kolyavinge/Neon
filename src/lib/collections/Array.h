#pragma once

#include <lib/Memory.h>
#include <lib/collections/Collection.h>
#include <lib/exceptions.h>

template<class T, int Count>
class Array : public Collection<T> {

    T _items[Count] = {};

public:
    Array() {
        initZero();
    }

    T& operator[](int index) override {
        checkBounds(index);
        return _items[index];
    }

    int getCount() override {
        return Count;
    }

    void initAll(T initValue) {
        for (int i = 0; i < Count; i++) {
            _items[i] = initValue;
        }
    }

    void initRange(int startIndex, int endIndex, T value) {
        for (int i = startIndex; i <= endIndex; i++) {
            _items[i] = value;
        }
    }

    void initZero() {
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
