#pragma once

#include <lib/system.h>

enum class Gear {
    reverse = -1,
    neutral = 0,
    first = 1,
    second = 2,
    third = 3,
    fourth = 4,
    fifth = 5,
    sixth = 6,
    _count = 8
};

class Gearbox : public Object {

    inline static const int _maxGearsCount = (int)Gear::_count;

    float _finalGearRatio;
    Array<float, (int)Gear::_count> _gearRatios;
    int _prevGearIndex;
    int _currentGearIndex;
    bool _isClutchActive;

public:
    Gearbox();
    void init();
    Gear getPrevGear();
    Gear getCurrentGear();
    float getCurrentGearRatio();
    bool shiftUp();
    bool shiftDown();
    bool isClutchActive();
    void activateClutch();
    void deactivateClutch();
    bool isEngineAndWheelsConnected();
};
