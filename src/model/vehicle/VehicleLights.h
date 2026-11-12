#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/Light.h>

class VehicleLights : public Object {

    Vector3 _frontCenter;
    Light _frontLeftLight;
    Light _frontRightLight;

public:
    Vector3 getFrontCenter();
    Light& getFrontLeftLight();
    Light& getFrontRightLight();
    void calculatePosition(
        Vector3 rightNormal, Vector3 frontNormal, Vector3 upNormal, Vector3 vehicleFrontCenterPoint, Vector3 color);
};
