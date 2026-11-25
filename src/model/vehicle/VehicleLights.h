#pragma once

#include <lib/SmoothValue.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/common/Light.h>

class VehicleLights : public Object {

    Vector3 _frontCenter;
    Light _frontLeftLight;
    Light _frontRightLight;

    Vector3 _rearBrakeLightColorFullIntensity;
    SmoothValue<float> _rearBrakeLightColorIntensity;
    Light _rearBrakeLight;
    Light _rearLeftSideLight;
    Light _rearRightSideLight;

public:
    void init(Vector3 frontLightsColor, Vector3 rearBrakeLightColor, Vector3 rearSideLightsColor, float rearLightsMaxDistance);
    Vector3 getFrontCenter();
    Light& getFrontLeftLight();
    Light& getFrontRightLight();
    Light& getRearBrakeLight();
    Light& getRearLeftSideLight();
    Light& getRearRightSideLight();
    bool isRearBrakeLightActive();
    void calculatePosition(
        Vector3 rightNormal, Vector3 frontNormal, Vector3 upNormal, Vector3 vehicleFrontCenterPoint, Vector3 vehicleRearCenterPoint);
    void update(float brakeRatio, float dt);
};
