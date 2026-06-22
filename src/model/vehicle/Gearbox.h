#pragma once

#include <lib/system.h>
#include <model/vehicle/Gear.h>
#include <model/vehicle/VehicleData.h>

enum class GearboxKind {
    manual,
    automatic
};

class Gearbox : public Object {

    inline static const int _maxGearsCount = (int)Gear::_count;

    VehicleData _data;
    Array<float, (int)Gear::_count> _gearRatios;
    int _prevGearIndex;
    int _currentGearIndex;
    bool _isClutchActive;

public:
    Gearbox();
    void init();
    GearboxKind getKind();
    Gear getPrevGear();
    Gear getCurrentGear();
    float getLowerGearRatio();
    float getCurrentGearRatio();
    bool shiftUp();
    bool shiftDown();
    bool isClutchActive();
    void activateClutch();
    void deactivateClutch();
    bool isEngineAndWheelsConnected();
};
