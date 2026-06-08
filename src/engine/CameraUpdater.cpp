#include <common/constants.h>
#include <engine/CameraUpdater.h>
#include <lib/calc/Geometry.h>
#include <lib/calc/UnitConverter.h>
#include <lib/calc/Vector3.h>

void CameraUpdater::update(Camera& camera, Vehicle& playerVehicle) {
    camera.setVerticalViewAngle(UnitConverter::degreesToRadians(40.0f));
    //setSideView(camera, playerVehicle);
    setBackView(camera, playerVehicle);
    //setTopView(camera, playerVehicle);
    camera.calculateViewMatrix();
    camera.calculateProjectionMatrix();
}

void CameraUpdater::setSideView(Camera& camera, Vehicle& playerVehicle) {
    Vector3 position = playerVehicle.getDriveAxle().getCenter();
    position.addMultiplied(playerVehicle.getChassis().getFrontNormal(), 10.0f);
    position.addMultiplied(playerVehicle.getChassis().getRightNormal(), 40.0f);
    position.addMultiplied(CommonConstants::upVector, 10.0f);
    camera.setPosition(position);

    Vector3 lookDirection = playerVehicle.getChassis().getRightNormal();
    lookDirection.mul(-1.0f);
    lookDirection.normalize();
    camera.setLookDirection(lookDirection);
}

void CameraUpdater::setBackView(Camera& camera, Vehicle& playerVehicle) {
    Vector3 position = playerVehicle.getDriveAxle().getCenter();
    position.subMultiplied(playerVehicle.getChassis().getFrontNormal(), 20.0f);
    position.addMultiplied(playerVehicle.getChassis().getRightNormal(), 1.0f);
    position.addMultiplied(CommonConstants::upVector, 8.0f);
    camera.setPosition(position);

    Vector3 lookDirection = playerVehicle.getChassis().getFrontNormal();
    lookDirection = Geometry::rotatePoint(lookDirection, -0.2f, playerVehicle.getChassis().getRightNormal(), CommonConstants::axisOrigin);
    lookDirection.normalize();
    camera.setLookDirection(lookDirection);
}

void CameraUpdater::setTopView(Camera& camera, Vehicle& playerVehicle) {
    Vector3 position = playerVehicle.getDriveAxle().getCenter();
    position.addMultiplied(playerVehicle.getChassis().getRightNormal(), 1.0f);
    position.addMultiplied(CommonConstants::upVector, 30.0f);
    camera.setPosition(position);

    Vector3 lookDirection(0, 0.01, -1);
    lookDirection.normalize();
    camera.setLookDirection(lookDirection);
}
