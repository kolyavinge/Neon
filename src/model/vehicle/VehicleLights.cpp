#include <common/constants.h>
#include <lib/SmoothValue.h>
#include <lib/calc/Math.h>
#include <model/vehicle/VehicleLights.h>

void VehicleLights::init(Vector3 frontLightsColor, Vector3 rearBrakeLightColor, Vector3 rearSideLightsColor) {
    _frontLeftLight.setColor(frontLightsColor);
    _frontRightLight.setColor(frontLightsColor);
    _rearBrakeLightColorFullIntensity = rearBrakeLightColor;
    _rearLeftSideLight.setColor(rearSideLightsColor);
    _rearRightSideLight.setColor(rearSideLightsColor);
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

Light& VehicleLights::getRearBrakeLight() {
    return _rearBrakeLight;
}

Light& VehicleLights::getRearLeftSideLight() {
    return _rearLeftSideLight;
}

Light& VehicleLights::getRearRightSideLight() {
    return _rearRightSideLight;
}

bool VehicleLights::isRearBrakeLightActive() {
    return _rearBrakeLightColorIntensity.getCurrentValue() > 0.0f;
}

void VehicleLights::calculatePosition(
    Vector3 rightNormal, Vector3 frontNormal, Vector3 upNormal, Vector3 vehicleFrontCenterPoint, Vector3 vehicleRearCenterPoint) {
    Vector3 position, direction;

    // front
    position = vehicleFrontCenterPoint;
    position.subMultiplied(rightNormal, 0.4f);
    direction = Math::rotatePoint(frontNormal, 0.2f, upNormal, CommonConstants::axisOrigin);
    _frontLeftLight.setPosition(position);
    _frontLeftLight.setDirection(direction);

    position = vehicleFrontCenterPoint;
    position.addMultiplied(rightNormal, 0.4f);
    direction = Math::rotatePoint(frontNormal, -0.2f, upNormal, CommonConstants::axisOrigin);
    _frontRightLight.setPosition(position);
    _frontRightLight.setDirection(direction);

    // rear brake
    position = vehicleRearCenterPoint;
    position.addMultiplied(frontNormal, 0.01f);
    position.subMultiplied(upNormal, 0.25f);
    direction = frontNormal;
    direction.mul(-1.0f);
    _rearBrakeLight.setPosition(position);
    _rearBrakeLight.setDirection(direction);

    // rear sides
    position = vehicleRearCenterPoint;
    position.subMultiplied(rightNormal, 0.7f);
    position.addMultiplied(frontNormal, 0.25f);
    position.subMultiplied(upNormal, 0.5f);
    direction = frontNormal;
    direction.mul(-1.0f);
    direction = Math::rotatePoint(direction, -Math::piQuarter - 0.35f, upNormal, CommonConstants::axisOrigin);
    _rearLeftSideLight.setPosition(position);
    _rearLeftSideLight.setDirection(direction);

    position = vehicleRearCenterPoint;
    position.addMultiplied(rightNormal, 0.7f);
    position.addMultiplied(frontNormal, 0.25f);
    position.subMultiplied(upNormal, 0.5f);
    direction = frontNormal;
    direction.mul(-1.0f);
    direction = Math::rotatePoint(direction, Math::piQuarter + 0.35f, upNormal, CommonConstants::axisOrigin);
    _rearRightSideLight.setPosition(position);
    _rearRightSideLight.setDirection(direction);

    _frontCenter = _frontLeftLight.getPosition().getMiddleTo(_frontRightLight.getPosition());
}

void VehicleLights::update(float brakeRatio, float dt) {
    _rearBrakeLightColorIntensity.setDestinationValue(brakeRatio > 0.0f ? 1.0f : 0.0f);
    _rearBrakeLightColorIntensity.update(8.0f * dt);
    Vector3 color = _rearBrakeLightColorFullIntensity;
    color.mul(_rearBrakeLightColorIntensity.getCurrentValue());
    _rearBrakeLight.setColor(color);
}
