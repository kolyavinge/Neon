#pragma once

#include <lib/Object.h>

class Random : public Object {

    inline static const double _a = 9459654965476;
    inline static const double _c = 6745675467549;
    inline static const double _m = 4643578547845;
    int _seed;
    double _x;

public:
    Random();
    int getSeed();
    void setSeed(int seed);
    int getInt(int min, int max);
    float getFloat(float min, float max);
};
