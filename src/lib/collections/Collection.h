#pragma once

#include <lib/Object.h>
#include <lib/collections/IComparator.h>

template<class T>
class Collection : public Object {

public:
    virtual T& operator[](int index) = 0;

    virtual int getCount() = 0;

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

    void sort(IComparator<T>& comparator) {
        sort(0, getCount() - 1, comparator);
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
