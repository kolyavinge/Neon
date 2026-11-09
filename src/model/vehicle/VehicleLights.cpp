#include <common/constants.h>
#include <lib/calc/Math.h>
#include <model/vehicle/VehicleLights.h>

DirectedLight& VehicleLights::getFrontLeftLight() {
    return _frontLeftLight;
}

DirectedLight& VehicleLights::getFrontRightLight() {
    return _frontRightLight;
}

void VehicleLights::calculatePosition(
    Vector3 rightNormal, Vector3 frontNormal, Vector3 upNormal, Vector3 vehicleFrontCenterPoint, Vector3 color) {
    Vector3 position = vehicleFrontCenterPoint;
    position.subMultiplied(rightNormal, 0.4f);
    Vector3 direction = Math::rotatePoint(frontNormal, 0.2f, upNormal, CommonConstants::axisOrigin);
    _frontLeftLight.setPosition(position);
    _frontLeftLight.setDirection(direction);
    _frontLeftLight.setColor(color);

    position = vehicleFrontCenterPoint;
    position.addMultiplied(rightNormal, 0.4f);
    direction = Math::rotatePoint(frontNormal, -0.2f, upNormal, CommonConstants::axisOrigin);
    _frontRightLight.setPosition(position);
    _frontRightLight.setDirection(direction);
    _frontRightLight.setColor(color);
}
