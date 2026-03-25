#pragma once

template<class T>
class IComparator {

public:
    virtual int Compare(T a, T b) = 0;
};
