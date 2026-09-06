#pragma once

#include <lib/Memory.h>
#include <lib/collections/Collection.h>
#include <lib/exceptions.h>

template<class T, int Count>
class Array : public Collection<T> {

    T _items[Count] = {};

public:
    Array() {}
    Array(const Array&) = default;
    Array& operator=(const Array&) = default;

    T& operator[](int index) override {
        checkBounds(index);
        return _items[index];
    }

    int getCount() const override {
        return Count;
    }

    void fillZero() requires std::is_scalar_v<T> {
        Memory::zero<T>(_items, Count);
    }

    void copyFrom(T* range, int count) {
        if (range == nullptr) throw ArgumentException(L"range cannot be null.");
        if (count < 0) throw ArgumentException(L"count must be greater than zero.");
        if (Count < count) throw ArgumentException(L"destination array count must be greater or equal than source array count.");
        for (int i = 0; i < count; i++) {
            _items[i] = range[i];
        }
    }

    T* getItemsPointer() {
        return _items;
    }

private:
    void checkBounds(int index) {
        if (index < 0) throw ArgumentException(L"index cannot be negative.");
        bool inBounds = 0 <= index && index < Count;
        if (!inBounds) throw IndexOutOfBoundsException();
    }
};
