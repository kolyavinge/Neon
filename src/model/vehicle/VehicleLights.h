#pragma once

#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/light.h>

class VehicleLights : public Object {

    DirectedLight _frontLeftLight;
    DirectedLight _frontRightLight;

public:
    DirectedLight& getFrontLeftLight();
    DirectedLight& getFrontRightLight();
    void calculatePosition(
        Vector3 rightNormal, Vector3 frontNormal, Vector3 upNormal, Vector3 vehicleFrontCenterPoint, Vector3 color);
};
