#pragma once

#include <lib/system.h>

template<class T>
class IComparator {

public:
    virtual ~IComparator() = default;
    virtual int compare(T a, T b) = 0;
};

template<class T>
class LambdaComparator : public Object, public IComparator<T> {

    int (*_func)(T a, T b);

public:
    LambdaComparator(int (*func)(T a, T b)) {
        _func = func;
    }

    int compare(T a, T b) override {
        return _func(a, b);
    }
};
