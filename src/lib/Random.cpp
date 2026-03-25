#include <ctime>
#include <lib/Random.h>
#include <math.h>

Random::Random() {
    _seed = (int)std::time(nullptr);
    _x = _seed;
}

int Random::getSeed() {
    return _seed;
}

void Random::setSeed(int seed) {
    _seed = seed;
    _x = _seed;
}

int Random::getInt(int min, int max) {
    _x = fmod((_a * _x + _c), _m);
    int result = (long long)_x % (max - min) + min;

    return result;
}

float Random::getFloat(float min, float max) {
    _x = fmod((_a * _x + _c), _m);
    double result = (_x / _m) * (max - min) + min;

    return (float)result;
}
