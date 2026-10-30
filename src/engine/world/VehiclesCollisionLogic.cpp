#include <engine/world/VehiclesCollisionLogic.h>
#include <lib/calc/Plane.h>
#include <lib/calc/TruncatedPlane.h>

VehiclesCollisionLogic::VehiclesCollisionLogic() {
    _anyCollisionsFound = false;
}

bool VehiclesCollisionLogic::resolveVehiclesCollision(Collection<Vehicle>& vehicles) {
    // ищим коллизии

    for (int i = 0; i < _collisionInfo.getCount(); i++) {
        _collisionInfo[i].collisionPoints.clear();
        _collisionInfo[i].collisionDepths.clear();
        _collisionInfo[i].collisionNormalsToBody.clear();
    }
    _anyCollisionsFound = false;

    findVehiclesCollision(vehicles);
    if (!_anyCollisionsFound) return false;

    // устраняем коллизии

    // расчитываем новые скорости в точках соударения

    // вытаскиваем точки из препятствий
    for (int i = 0; i < vehicles.getCount(); i++) {
        Vehicle& vehicle = vehicles[i];
        VehicleCollisionInfo& collisionInfo = _collisionInfo[vehicle.getId()];
        if (collisionInfo.collisionPoints.getCount() == 0) continue;
        Vector3 longestCollisionDepth = Vector3::getLongest(collisionInfo.collisionDepths);
        vehicle.moveByVector(longestCollisionDepth);
    }

    return true;
}

void VehiclesCollisionLogic::findVehiclesCollision(Collection<Vehicle>& vehicles) {
    for (int i = 0; i < vehicles.getCount(); i++) {
        // if (vehicles[i].isFrozen()) continue;
        vehicles[i].getBody().calculateBottomTruncatedPlane();
        vehicles[i].getBody().calculateSideTruncatedPlanes();
    }
    float maxVehicleCollisionLengthSquared = vehicles.first().getData().maxVehicleCollisionLengthSquared;
    for (int i = 0; i < vehicles.getCount() - 1; i++) {
        Vehicle& vehicleA = vehicles[i];
        // if (vehicle.isFrozen(vehicleA)) continue;
        for (int j = i + 1; j < vehicles.getCount(); j++) {
            Vehicle& vehicleB = vehicles[j];
            float lengthSquaredBetweenVehicles = vehicleA.getCenter().getLengthSquaredTo(vehicleB.getCenter());
            if (lengthSquaredBetweenVehicles > maxVehicleCollisionLengthSquared) continue;
            _anyCollisionsFound |= findCollisionDepth(vehicleA, vehicleB) || findCollisionDepth(vehicleB, vehicleA);
        }
    }
}

bool VehiclesCollisionLogic::findCollisionDepth(Vehicle& vehicleA, Vehicle& vehicleB) {
    Vector3 vehicleACollisionPointTo;
    int vehicleACollisionPointIndex;
    if (!hasCollision(vehicleA.getBody(), vehicleB.getBody(), output vehicleACollisionPointTo, output vehicleACollisionPointIndex)) return false;
    Vector3 vehicleACollisionPointFrom = *vehicleA.getBody().getBox().getOppositeDiagonalPointFor(vehicleACollisionPointIndex);
    Collection<TruncatedPlane>& vehicleBSidePlanes = vehicleB.getBody().getSideTruncatedPlanes();
    for (int i = 0; i < vehicleBSidePlanes.getCount(); i++) {
        if (findCollisionDepthForBodySide(vehicleA.getId(), vehicleBSidePlanes[i], vehicleACollisionPointFrom, vehicleACollisionPointTo)) {
            return true;
        }
    }
    throw AssertException();
}

bool VehiclesCollisionLogic::hasCollision(
    Body& vehicleBodyA, Body& vehicleBodyB, output Vector3& vehicleACollisionPoint, output int& vehicleACollisionPointIndex) {
    Collection<Vector3*>& vehicleABodyPoints = vehicleBodyA.getBox().getPoints();
    for (int i = 0; i < vehicleABodyPoints.getCount(); i++) {
        if (vehicleBodyB.isPointInside(*vehicleABodyPoints[i])) {
            vehicleACollisionPoint = *vehicleABodyPoints[i];
            vehicleACollisionPointIndex = i;
            return true;
        }
    }

    return false;
}

bool VehiclesCollisionLogic::findCollisionDepthForBodySide(int vehicleAId, Plane& vehicleBSidePlane, Vector3 rayFrom, Vector3 rayTo) {
    Vector3 _;
    if (!vehicleBSidePlane.hasCollision(rayFrom, rayTo, 0.01f, output _)) return false;
    Vector3 collisionPoint = vehicleBSidePlane.getProjectedPoint(rayTo);
    Vector3 collisionDepth = rayTo.getDirectionTo(collisionPoint);
    VehicleCollisionInfo& collisionInfo = _collisionInfo[vehicleAId];
    collisionInfo.collisionPoints.add(collisionPoint);
    collisionInfo.collisionDepths.add(collisionDepth);
    collisionInfo.collisionNormalsToBody.addByValue(vehicleBSidePlane.getFrontNormal());

    return true;
}
