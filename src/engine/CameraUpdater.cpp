#include <engine/CameraUpdater.h>
#include <lib/calc/UnitConverter.h>

void CameraUpdater::update(Camera& camera, Vehicle& playerVehicle) {
    camera.setVerticalViewAngle(UnitConverter::degreesToRadians(40.0f));
    camera.setPosition(playerVehicle.getDriveAxle().getCenter());
    camera.setLookDirection(playerVehicle.getChassis().getFrontNormal());
    camera.calculateViewMatrix();
    camera.calculateProjectionMatrix();
}
