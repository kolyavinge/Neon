#include <engine/world/VehiclesCollisionLogic.h>
#include <lib/calc/Plane.h>
#include <model/vehicle/Body.h>

bool VehiclesCollisionLogic::resolveVehiclesCollision(Collection<Vehicle*>& vehicles) {
    // ищим коллизии

    _collisionPoints.clear();
    _collisionDepths.clear();
    _collisionNormalsToBody.clear();
    findVehiclesCollision(vehicles);
    if (_collisionPoints.getCount() == 0) return false;

    // устраняем коллизии

    // расчитываем новые скорости в точках соударения

    return true;
}

void VehiclesCollisionLogic::findVehiclesCollision(Collection<Vehicle*>& vehicles) {
    float maxVehicleCollisionLengthSquared = vehicles.first()->getData().maxVehicleCollisionLengthSquared;
    for (int i = 0; i < vehicles.getCount() - 1; i++) {
        Vehicle& vehicleA = *vehicles[i];
        for (int j = i + 1; j < vehicles.getCount(); j++) {
            Vehicle& vehicleB = *vehicles[j];
            float lengthSquaredBetweenVehicles = vehicleA.getCenter().getLengthSquaredTo(vehicleB.getCenter());
            if (lengthSquaredBetweenVehicles > maxVehicleCollisionLengthSquared) continue;
            findCollisionDepth(vehicleA, vehicleB);
            findCollisionDepth(vehicleB, vehicleA);
        }
    }
}

void VehiclesCollisionLogic::findCollisionDepth(Vehicle& vehicleA, Vehicle& vehicleB) {
    Vector3 vehicleACollisionPoint;
    if (!hasCollision(vehicleA, vehicleB, output vehicleACollisionPoint)) return;
    Vector3 collisionPointVelocity = vehicleA.getBody().getVelocityAtPoint(vehicleACollisionPoint);
    Vector3 collisionPointFrom = vehicleACollisionPoint;
    collisionPointFrom.sub(collisionPointVelocity);

    Vector3 chassisFrontNormal = vehicleA.getChassisFrontNormal();
    Vector3 chassisBackNormal = chassisFrontNormal;
    chassisBackNormal.mul(-1.0f);
    Vector3 chassisRightNormal = vehicleA.getChassisRightNormal();
    Vector3 chassisLeftNormal = chassisRightNormal;
    chassisLeftNormal.mul(-1.0f);
    Collection<Vector3*>& bodyPoints = vehicleA.getBody().getBox().getPoints();
    Vector3 upLeftBodyPoint = *bodyPoints[(int)Box3dPoint::bottomUpLeft];
    Vector3 downRightBodyPoint = *bodyPoints[(int)Box3dPoint::bottomDownRight];

    findCollisionDepthForBodySide(Plane(chassisLeftNormal, upLeftBodyPoint), collisionPointFrom, vehicleACollisionPoint) ||
        findCollisionDepthForBodySide(Plane(chassisFrontNormal, upLeftBodyPoint), collisionPointFrom, vehicleACollisionPoint) ||
        findCollisionDepthForBodySide(Plane(chassisRightNormal, downRightBodyPoint), collisionPointFrom, vehicleACollisionPoint) ||
        findCollisionDepthForBodySide(Plane(chassisBackNormal, downRightBodyPoint), collisionPointFrom, vehicleACollisionPoint);
}

bool VehiclesCollisionLogic::findCollisionDepthForBodySide(Plane bodySide, Vector3 rayFrom, Vector3 rayTo) {
    Vector3 _;
    if (!bodySide.hasCollision(rayFrom, rayTo, 0.01f, _)) return false;
    Vector3 collisionPoint = bodySide.getProjectedPoint(rayTo);
    Vector3 collisionDepth = rayFrom.getDirectionTo(collisionPoint);
    _collisionPoints.add(collisionPoint);
    _collisionDepths.add(collisionDepth);
    _collisionNormalsToBody.addByValue(bodySide.getFrontNormal());

    return true;
}

bool VehiclesCollisionLogic::hasCollision(Vehicle& vehicleA, Vehicle& vehicleB, output Vector3& vehicleACollisionPoint) {
    Collection<Vector3*>& vehicleABodyPoints = vehicleA.getBody().getBox().getPoints();
    Body& vehicleBBody = vehicleB.getBody();
    for (int i = 0; i < vehicleABodyPoints.getCount(); i++) {
        if (vehicleBBody.isPointInside(*vehicleABodyPoints[i])) {
            vehicleACollisionPoint = *vehicleABodyPoints[i];
            return true;
        }
    }

    return false;
}
