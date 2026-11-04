#include <common/constants.h>
#include <engine/common/CameraUpdater.h>
#include <lib/calc/Math.h>
#include <lib/calc/Vector3.h>

void CameraUpdater::update(Camera& camera, Vehicle& vehicle) {
    camera.setVerticalViewAngle(CommonConstants::verticalFieldOfView);

    //setLeftSideView(camera, vehicle);
    //setRightSideView(camera, vehicle);
    setBackSideView(camera, vehicle);
    //setMirrorView(camera, vehicle);
    //setTopView(camera, vehicle);
    //setWheelCenterView(camera, vehicle);
    //setRightSideStaticView(camera, vehicle);
    //setAirView(camera, vehicle);

    camera.calculateViewMatrix();
    camera.calculateProjectionMatrix();
    camera.calculateFrustumPlanes();
}

void CameraUpdater::setLeftSideView(Camera& camera, Vehicle& vehicle) {
    Vector3 position = vehicle.getCenter();
    position.addMultiplied(vehicle.getChassisFrontNormal(), 2.0f);
    position.subMultiplied(vehicle.getChassisRightNormal(), 6.0f);
    position.addMultiplied(CommonConstants::upAxis, 2.0f);
    Vector3 lookDirection = vehicle.getChassisRightNormal();
    lookDirection = Math::rotatePoint(lookDirection, 0.2f, vehicle.getChassisFrontNormal(), CommonConstants::axisOrigin);
    camera.setPosition(position);
    camera.setLookDirection(lookDirection);
}

void CameraUpdater::setRightSideView(Camera& camera, Vehicle& vehicle) {
    Vector3 position = vehicle.getCenter();
    position.addMultiplied(vehicle.getChassisFrontNormal(), 2.0f);
    position.addMultiplied(vehicle.getChassisRightNormal(), 6.0f);
    position.addMultiplied(CommonConstants::upAxis, 2.0f);
    Vector3 lookDirection = vehicle.getChassisRightNormal();
    lookDirection.mul(-1.0f);
    lookDirection = Math::rotatePoint(lookDirection, -0.2f, vehicle.getChassisFrontNormal(), CommonConstants::axisOrigin);
    camera.setPosition(position);
    camera.setLookDirection(lookDirection);
}

void CameraUpdater::setBackSideView(Camera& camera, Vehicle& vehicle) {
    Vector3 position = vehicle.getCenter();
    position.subMultiplied(vehicle.getChassisFrontNormal(), 5.5f);
    position.addMultiplied(CommonConstants::upAxis, 2.5f);
    Vector3 cameraRightNormal = Vector3::getRightNormal(vehicle.getChassisFrontNormal(), CommonConstants::upAxis);
    Vector3 lookDirection = vehicle.getChassisFrontNormal();
    lookDirection = Math::rotatePoint(lookDirection, -0.25f, cameraRightNormal, CommonConstants::axisOrigin);
    camera.setPosition(position);
    camera.setLookDirection(lookDirection);
}

void CameraUpdater::setMirroredView(Camera& camera, Vehicle& vehicle) {
    Vector3 position = vehicle.getCenter();
    position.addMultiplied(vehicle.getChassisFrontNormal(), 6.0f);
    position.addMultiplied(CommonConstants::upAxis, 2.5f);
    Vector3 cameraRightNormal = Vector3::getRightNormal(vehicle.getChassisFrontNormal(), CommonConstants::upAxis);
    Vector3 lookDirection = vehicle.getChassisFrontNormal();
    lookDirection.mul(-1.0f);
    lookDirection = Math::rotatePoint(lookDirection, 0.25f, cameraRightNormal, CommonConstants::axisOrigin);
    camera.setPosition(position);
    camera.setLookDirection(lookDirection);
}

void CameraUpdater::setTopSideView(Camera& camera, Vehicle& vehicle) {
    Vector3 position = vehicle.getCenter();
    position.addMultiplied(vehicle.getChassisFrontNormal(), 1.0f);
    position.addMultiplied(CommonConstants::upAxis, 6.0f);
    Vector3 lookDirection(0.0f, 0.01f, -1.0f);
    camera.setPosition(position);
    camera.setLookDirection(lookDirection);
}

void CameraUpdater::setWheelCenterView(Camera& camera, Vehicle& vehicle) {
    Vector3 position = vehicle.getWheel(1).getCenter();
    position.addMultiplied(vehicle.getChassisRightNormal(), 1.5f);
    Vector3 lookDirection = vehicle.getChassisRightNormal();
    lookDirection.mul(-1.0f);
    camera.setPosition(position);
    camera.setLookDirection(lookDirection);
}

void CameraUpdater::setRightSideStaticView(Camera& camera, Vehicle& vehicle) {
    Vector3 position = vehicle.getCenter();
    position.addMultiplied(CommonConstants::rightAxis, 6.0f);
    position.addMultiplied(CommonConstants::upAxis, 1.0f);
    Vector3 lookDirection = CommonConstants::rightAxis;
    lookDirection.mul(-1.0f);
    camera.setPosition(position);
    camera.setLookDirection(lookDirection);
}

void CameraUpdater::setAirView(Camera& camera, Vehicle& vehicle) {
    Vector3 position = vehicle.getCenter();
    position.addMultiplied(CommonConstants::upAxis, 10.0f);
    Vector3 lookDirection = CommonConstants::upAxis;
    lookDirection.mul(-1.0f);
    lookDirection.y += 0.001f;
    camera.setPosition(position);
    camera.setLookDirection(lookDirection);
}
