#include <common/constants.h>
#include <engine/CameraUpdater.h>
#include <lib/calc/Math.h>
#include <lib/calc/Vector3.h>

void CameraUpdater::update(Camera& camera, Vehicle& playerVehicle) {
    camera.setVerticalViewAngle(CommonConstants::verticalFieldOfView);
    //setLeftSideView(camera, playerVehicle);
    setRightSideView(camera, playerVehicle);
    //setBackView(camera, playerVehicle);
    //setSideBackView(camera, playerVehicle);
    //setTopView(camera, playerVehicle);
    //setWheelCenterView(camera, playerVehicle);
    camera.calculateViewMatrix();
    camera.calculateProjectionMatrix();
}

void CameraUpdater::setLeftSideView(Camera& camera, Vehicle& playerVehicle) {
    Vector3 position = playerVehicle.getCenter();
    position.addMultiplied(playerVehicle.getChassisFrontNormal(), 2.0f);
    position.subMultiplied(playerVehicle.getChassisRightNormal(), 6.0f);
    position.addMultiplied(CommonConstants::upAxis, 2.0f);
    camera.setPosition(position);
    Vector3 lookDirection = playerVehicle.getChassisRightNormal();
    lookDirection = Math::rotatePoint(lookDirection, 0.2f, playerVehicle.getChassisFrontNormal(), CommonConstants::axisOrigin);
    lookDirection.normalize();
    camera.setLookDirection(lookDirection);
}

void CameraUpdater::setRightSideView(Camera& camera, Vehicle& playerVehicle) {
    Vector3 position = playerVehicle.getCenter();
    position.addMultiplied(playerVehicle.getChassisFrontNormal(), 2.0f);
    position.addMultiplied(playerVehicle.getChassisRightNormal(), 6.0f);
    position.addMultiplied(CommonConstants::upAxis, 2.0f);
    camera.setPosition(position);
    Vector3 lookDirection = playerVehicle.getChassisRightNormal();
    lookDirection.mul(-1.0f);
    lookDirection = Math::rotatePoint(lookDirection, -0.2f, playerVehicle.getChassisFrontNormal(), CommonConstants::axisOrigin);
    lookDirection.normalize();
    camera.setLookDirection(lookDirection);
}

void CameraUpdater::setBackView(Camera& camera, Vehicle& playerVehicle) {
    Vector3 position = playerVehicle.getCenter();
    position.subMultiplied(playerVehicle.getChassisFrontNormal(), 4.0f);
    position.addMultiplied(CommonConstants::upAxis, 2.0f);
    camera.setPosition(position);
    Vector3 lookDirection = playerVehicle.getChassisFrontNormal();
    lookDirection = Math::rotatePoint(lookDirection, -0.2f, playerVehicle.getChassisRightNormal(), CommonConstants::axisOrigin);
    lookDirection.normalize();
    camera.setLookDirection(lookDirection);
}

void CameraUpdater::setSideBackView(Camera& camera, Vehicle& playerVehicle) {
    Vector3 position = playerVehicle.getCenter();
    position.subMultiplied(playerVehicle.getChassisFrontNormal(), 4.0f);
    position.addMultiplied(playerVehicle.getChassisRightNormal(), 2.5f);
    position.addMultiplied(CommonConstants::upAxis, 2.0f);
    camera.setPosition(position);
    Vector3 lookDirection = playerVehicle.getChassisFrontNormal();
    lookDirection = Math::rotatePoint(lookDirection, -0.2f, playerVehicle.getChassisRightNormal(), CommonConstants::axisOrigin);
    lookDirection.normalize();
    camera.setLookDirection(lookDirection);
}

void CameraUpdater::setTopView(Camera& camera, Vehicle& playerVehicle) {
    Vector3 position = playerVehicle.getCenter();
    position.addMultiplied(playerVehicle.getChassisFrontNormal(), 1.0f);
    position.addMultiplied(CommonConstants::upAxis, 6.0f);
    camera.setPosition(position);
    Vector3 lookDirection(0.0f, 0.01f, -1.0f);
    lookDirection.normalize();
    camera.setLookDirection(lookDirection);
}

void CameraUpdater::setWheelCenterView(Camera& camera, Vehicle& playerVehicle) {
    Vector3 position = playerVehicle.getWheel(1).getCenter();
    position.addMultiplied(playerVehicle.getChassisRightNormal(), 1.5f);
    camera.setPosition(position);
    Vector3 lookDirection = playerVehicle.getChassisRightNormal();
    lookDirection.mul(-1.0f);
    camera.setLookDirection(lookDirection);
}
