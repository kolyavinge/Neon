#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>

class WheelLogic : public Object {

public:
    void calculateNormalsBySteeringAngle(
        float steeringAngle,
        Vector3& chassisFrontNormal,
        Vector3& chassisTopNormal,
        output Vector3& newWheelFrontNormal,
        output Vector3& newLeftWheelOutsideNormal,
        output Vector3& newRightWheelOutsideNormal);
};
