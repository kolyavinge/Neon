#include <common/constants.h>
#include <engine/CameraUpdater.h>
#include <lib/calc/Math.h>
#include <lib/calc/Vector3.h>

void CameraUpdater::update(Camera& camera, Vehicle& playerVehicle) {
    camera.setVerticalViewAngle(CommonConstants::verticalFieldOfView);
    //setSideView(camera, playerVehicle);
    setBackView(camera, playerVehicle);
    //setTopView(camera, playerVehicle);
    camera.calculateViewMatrix();
    camera.calculateProjectionMatrix();
}

void CameraUpdater::setSideView(Camera& camera, Vehicle& playerVehicle) {
    Vector3 position = playerVehicle.getDriveAxle().getCenter();
    position.addMultiplied(playerVehicle.getChassis().getFrontNormal(), 1.0f);
    position.addMultiplied(playerVehicle.getChassis().getRightNormal(), 8.0f);
    position.addMultiplied(CommonConstants::upVector, 2.5f);
    camera.setPosition(position);

    Vector3 lookDirection = playerVehicle.getChassis().getRightNormal();
    lookDirection.mul(-1.0f);
    lookDirection = Math::rotatePoint(lookDirection, -0.2f, playerVehicle.getChassis().getFrontNormal(), CommonConstants::axisOrigin);
    lookDirection.normalize();
    camera.setLookDirection(lookDirection);
}

void CameraUpdater::setBackView(Camera& camera, Vehicle& playerVehicle) {
    Vector3 position = playerVehicle.getDriveAxle().getCenter();
    position.subMultiplied(playerVehicle.getChassis().getFrontNormal(), 4.0f);
    position.addMultiplied(playerVehicle.getChassis().getRightNormal(), 1.0f);
    position.addMultiplied(CommonConstants::upVector, 2.0f);
    camera.setPosition(position);

    Vector3 lookDirection = playerVehicle.getChassis().getFrontNormal();
    lookDirection = Math::rotatePoint(lookDirection, -0.2f, playerVehicle.getChassis().getRightNormal(), CommonConstants::axisOrigin);
    lookDirection.normalize();
    camera.setLookDirection(lookDirection);
}

void CameraUpdater::setTopView(Camera& camera, Vehicle& playerVehicle) {
    Vector3 position = playerVehicle.getDriveAxle().getCenter();
    position.addMultiplied(playerVehicle.getChassis().getFrontNormal(), 2.0f);
    //position.addMultiplied(playerVehicle.getChassis().getRightNormal(), 1.0f);
    position.addMultiplied(CommonConstants::upVector, 10.0f);
    camera.setPosition(position);

    Vector3 lookDirection(0.0f, 0.01f, -1.0f);
    lookDirection.normalize();
    camera.setLookDirection(lookDirection);
}
