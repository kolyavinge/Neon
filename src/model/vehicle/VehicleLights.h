#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/light.h>

class VehicleLights : public Object {

    Vector3 _frontCenter;
    DirectedLight _frontLeftLight;
    DirectedLight _frontRightLight;

public:
    Vector3 getFrontCenter();
    DirectedLight& getFrontLeftLight();
    DirectedLight& getFrontRightLight();
    void calculatePosition(
        Vector3 rightNormal, Vector3 frontNormal, Vector3 upNormal, Vector3 vehicleFrontCenterPoint, Vector3 color);
};
