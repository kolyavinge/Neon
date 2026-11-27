#pragma once

#include <concepts>
#include <lib/Memory.h>
#include <lib/collections/Collection.h>
#include <lib/exceptions.h>
#include <type_traits>

template <auto Size>
concept ConvertibleToPositiveInt =
(requires { int{ Size }; } || std::is_enum_v<decltype(Size)>) &&
(static_cast<int>(Size) > 0);

template<class T, auto Size> requires ConvertibleToPositiveInt<Size>
class Array : public Collection<T> {

public:
    static constexpr int Count = static_cast<int>(Size);

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
    T _items[Count] = {};

    void checkBounds(int index) {
        if (index < 0) throw ArgumentException(L"index cannot be negative.");
        bool inBounds = 0 <= index && index < Count;
        if (!inBounds) throw IndexOutOfBoundsException();
    }
};

template<class T, auto Dimention1, auto Dimention2>
    requires ConvertibleToPositiveInt<Dimention1>&& ConvertibleToPositiveInt<Dimention2>
class Array2d : public Array<Array<T, Dimention2>, Dimention1> {};
