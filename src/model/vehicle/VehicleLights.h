#pragma once

#include <lib/SmoothValue.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/Light.h>

class VehicleLights : public Object {

    Vector3 _frontCenter;
    Light _frontLeftLight;
    Light _frontRightLight;

    Vector3 _rearLightsColorFullIntensity;
    SmoothValue<float> _rearLightsColorIntensity;
    Light _rearLight;

public:
    void init(Vector3 frontLightsColor, Vector3 rearLightsColor);
    Vector3 getFrontCenter();
    Light& getFrontLeftLight();
    Light& getFrontRightLight();
    Light& getRearLight();
    void calculatePosition(
        Vector3 rightNormal, Vector3 frontNormal, Vector3 upNormal, Vector3 vehicleFrontCenterPoint, Vector3 vehicleRearCenterPoint);
    void update(float brakeRatio, float dt);
};
