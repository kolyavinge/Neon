#pragma once

#include <lib/collections/Collection.h>

template<class T>
class Span : public Collection<T> {

    Collection<T>& _collection;
    int _startIndex;
    int _count;

public:
    Span(Collection<T>& collection, int startIndex, int count = -1) :
        _collection(collection) {
        _startIndex = startIndex;
        _count = count != -1 ? count : collection.getCount() - startIndex;
    }

    T& operator[](int index) override {
        if (index >= _count) throw IndexOutOfBoundsException();
        return _collection[_startIndex + index];
    }

    int getCount() const override {
        return _count;
    }
};
