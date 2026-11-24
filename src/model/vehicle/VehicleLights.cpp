#include <common/constants.h>
#include <lib/SmoothValue.h>
#include <lib/calc/Math.h>
#include <model/vehicle/VehicleLights.h>

void VehicleLights::init(Vector3 frontLightsColor, Vector3 rearLightsColor) {
    _frontLeftLight.setColor(frontLightsColor);
    _frontRightLight.setColor(frontLightsColor);
    _rearLightsColorFullIntensity = rearLightsColor;
}

Vector3 VehicleLights::getFrontCenter() {
    return _frontCenter;
}

Light& VehicleLights::getFrontLeftLight() {
    return _frontLeftLight;
}

Light& VehicleLights::getFrontRightLight() {
    return _frontRightLight;
}

Light& VehicleLights::getRearLight() {
    return _rearLight;
}

void VehicleLights::calculatePosition(
    Vector3 rightNormal, Vector3 frontNormal, Vector3 upNormal, Vector3 vehicleFrontCenterPoint, Vector3 vehicleRearCenterPoint) {
    Vector3 position = vehicleFrontCenterPoint;
    position.subMultiplied(rightNormal, 0.4f);
    Vector3 direction = Math::rotatePoint(frontNormal, 0.2f, upNormal, CommonConstants::axisOrigin);
    _frontLeftLight.setPosition(position);
    _frontLeftLight.setDirection(direction);

    position = vehicleFrontCenterPoint;
    position.addMultiplied(rightNormal, 0.4f);
    direction = Math::rotatePoint(frontNormal, -0.2f, upNormal, CommonConstants::axisOrigin);
    _frontRightLight.setPosition(position);
    _frontRightLight.setDirection(direction);

    position = vehicleRearCenterPoint;
    position.addMultiplied(frontNormal, 0.01f);
    position.subMultiplied(upNormal, 0.25f);
    direction = frontNormal;
    direction.mul(-1.0f);
    _rearLight.setPosition(position);
    _rearLight.setDirection(direction);

    _frontCenter = _frontLeftLight.getPosition().getMiddleTo(_frontRightLight.getPosition());
}

void VehicleLights::update(float brakeRatio, float dt) {
    _rearLightsColorIntensity.setDestinationValue(brakeRatio > 0.0f ? 1.0f : 0.0f);
    _rearLightsColorIntensity.update(8.0f * dt);
    Vector3 color = _rearLightsColorFullIntensity;
    color.mul(_rearLightsColorIntensity.getCurrentValue());
    _rearLight.setColor(color);
}
