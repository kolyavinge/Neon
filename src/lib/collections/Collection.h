#pragma once

#include <lib/Object.h>
#include <lib/collections/IComparator.h>

template<class T>
class Collection : public Object {

public:
    virtual T& operator[](int index) = 0;

    virtual int getCount() const = 0;

    T& first() {
        return (*this)[0];
    }

    T& last() {
        return (*this)[getCount() - 1];
    }

    int getIndexOf(const T& item) {
        for (int i = 0; i < getCount(); i++) {
            if (item == (*this)[i]) {
                return i;
            }
        }

        return -1;
    }

    void initAll(T initValue) {
        for (int i = 0; i < getCount(); i++) {
            (*this)[i] = initValue;
        }
    }

    void initRange(int startIndex, int endIndex, T value) {
        for (int i = startIndex; i <= endIndex; i++) {
            (*this)[i] = value;
        }
    }

    void sort(IComparator<T>& comparator) {
        sort(0, getCount() - 1, comparator);
    }

    int getSizeInBytes() {
        return getCount() * (int)sizeof(T);
    }

private:
    void sort(int startIndex, int endIndex, IComparator<T>& comparator) {
        int i = startIndex;
        int j = endIndex;
        T& middle = (*this)[(i + j) / 2];
        while (i <= j) {
            while (comparator.Compare((*this)[i], middle) < 0) i++;
            while (comparator.Compare((*this)[j], middle) > 0) j--;
            if (i <= j) {
                T temp = (*this)[i];
                (*this)[i] = (*this)[j];
                (*this)[j] = temp;
                i++;
                j--;
            }
        }
        if (j > startIndex) sort(startIndex, j, comparator);
        if (i < endIndex) sort(i, endIndex, comparator);
    }
};
