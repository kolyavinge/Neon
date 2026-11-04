#include <common/constants.h>
#include <lib/calc/Math.h>
#include <lib/calc/Vector3.h>
#include <model/common/cameras.h>

void LeftSideCamera::innerUpdate(Vehicle& vehicle) {
    Vector3 position = vehicle.getCenter();
    position.addMultiplied(vehicle.getChassisFrontNormal(), 2.0f);
    position.subMultiplied(vehicle.getChassisRightNormal(), 6.0f);
    position.addMultiplied(CommonConstants::upAxis, 2.0f);
    Vector3 lookDirection = vehicle.getChassisRightNormal();
    lookDirection = Math::rotatePoint(lookDirection, 0.2f, vehicle.getChassisFrontNormal(), CommonConstants::axisOrigin);
    setPosition(position);
    setLookDirection(lookDirection);
}

void RightSideCamera::innerUpdate(Vehicle& vehicle) {
    Vector3 position = vehicle.getCenter();
    position.addMultiplied(vehicle.getChassisFrontNormal(), 2.0f);
    position.addMultiplied(vehicle.getChassisRightNormal(), 6.0f);
    position.addMultiplied(CommonConstants::upAxis, 2.0f);
    Vector3 lookDirection = vehicle.getChassisRightNormal();
    lookDirection.mul(-1.0f);
    lookDirection = Math::rotatePoint(lookDirection, -0.2f, vehicle.getChassisFrontNormal(), CommonConstants::axisOrigin);
    setPosition(position);
    setLookDirection(lookDirection);
}

void BackSideCamera::innerUpdate(Vehicle& vehicle) {
    Vector3 position = vehicle.getCenter();
    position.subMultiplied(vehicle.getChassisFrontNormal(), 5.5f);
    position.addMultiplied(CommonConstants::upAxis, 2.5f);
    Vector3 cameraRightNormal = Vector3::getRightNormal(vehicle.getChassisFrontNormal(), CommonConstants::upAxis);
    Vector3 lookDirection = vehicle.getChassisFrontNormal();
    lookDirection = Math::rotatePoint(lookDirection, -0.25f, cameraRightNormal, CommonConstants::axisOrigin);
    setPosition(position);
    setLookDirection(lookDirection);
}

void MirroredCamera::innerUpdate(Vehicle& vehicle) {
    Vector3 position = vehicle.getCenter();
    position.addMultiplied(vehicle.getChassisFrontNormal(), 6.0f);
    position.addMultiplied(CommonConstants::upAxis, 2.5f);
    Vector3 cameraRightNormal = Vector3::getRightNormal(vehicle.getChassisFrontNormal(), CommonConstants::upAxis);
    Vector3 lookDirection = vehicle.getChassisFrontNormal();
    lookDirection.mul(-1.0f);
    lookDirection = Math::rotatePoint(lookDirection, 0.25f, cameraRightNormal, CommonConstants::axisOrigin);
    setPosition(position);
    setLookDirection(lookDirection);
}

void TopSideCamera::innerUpdate(Vehicle& vehicle) {
    Vector3 position = vehicle.getCenter();
    position.addMultiplied(vehicle.getChassisFrontNormal(), 1.0f);
    position.addMultiplied(CommonConstants::upAxis, 6.0f);
    Vector3 lookDirection(0.0f, 0.01f, -1.0f);
    setPosition(position);
    setLookDirection(lookDirection);
}

void WheelCenterCamera::innerUpdate(Vehicle& vehicle) {
    Vector3 position = vehicle.getWheel(1).getCenter();
    position.addMultiplied(vehicle.getChassisRightNormal(), 1.5f);
    Vector3 lookDirection = vehicle.getChassisRightNormal();
    lookDirection.mul(-1.0f);
    setPosition(position);
    setLookDirection(lookDirection);
}

void RightSideStaticCamera::innerUpdate(Vehicle& vehicle) {
    Vector3 position = vehicle.getCenter();
    position.addMultiplied(CommonConstants::rightAxis, 6.0f);
    position.addMultiplied(CommonConstants::upAxis, 1.0f);
    Vector3 lookDirection = CommonConstants::rightAxis;
    lookDirection.mul(-1.0f);
    setPosition(position);
    setLookDirection(lookDirection);
}

void AirCamera::innerUpdate(Vehicle& vehicle) {
    Vector3 position = vehicle.getCenter();
    position.addMultiplied(CommonConstants::upAxis, 10.0f);
    Vector3 lookDirection = CommonConstants::upAxis;
    lookDirection.mul(-1.0f);
    lookDirection.y += 0.001f;
    setPosition(position);
    setLookDirection(lookDirection);
}
