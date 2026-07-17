#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/vehicle/Wheel.h>

class WheelLogic : public Object {

public:
    void updateFrontAndOutsideNormals(
        float steeringAngle,
        Vector3 chassisRightNormal,
        Vector3 chassisFrontNormal,
        Vector3 chassisUpNormal,
        Wheel& frontLeftWheel,
        Wheel& frontRightWheel,
        Wheel& rearLeftWheel,
        Wheel& rearRightWheel);

    void calculateNormalsBySteeringAngle(
        float steeringAngle,
        Vector3 chassisFrontNormal,
        Vector3 chassisUpNormal,
        output Vector3& newWheelFrontNormal,
        output Vector3& newLeftWheelOutsideNormal,
        output Vector3& newRightWheelOutsideNormal);
};
