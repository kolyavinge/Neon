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
        _collisionInfo[i].anotherVehicleId.clear();
    }
    _anyCollisionsFound = false;
    findVehiclesCollision(vehicles);
    _calculatedBodyPlanesCache.fillZero();
    if (!_anyCollisionsFound) return false;

    // устраняем коллизии

    // расчитываем новые скорости в точках соударения
    for (int i = 0; i < _collisionInfo.getCount(); i++) {
        Vehicle& vehicle = vehicles[i];
        VehicleCollisionInfo& collisionInfo = _collisionInfo[vehicle.getId()];
        if (collisionInfo.collisionPoints.getCount() == 0) continue;
        for (int j = 0; j < collisionInfo.collisionPoints.getCount(); j++) {
            Vehicle& anotherVehicle = vehicles[collisionInfo.anotherVehicleId[j]];
            vehicle.calculateVelocitiesAfterCollisionToAnotherVehicle(
                collisionInfo.collisionPoints[j], collisionInfo.collisionDepths[j].getNormalized(), anotherVehicle);
        }
    }

    // вытаскиваем точки кузова из другой машины
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
    float maxVehicleCollisionLengthSquared = vehicles.first().getData().maxVehicleCollisionLengthSquared;
    for (int i = 0; i < vehicles.getCount() - 1; i++) {
        Vehicle& vehicleA = vehicles[i];
        for (int j = i + 1; j < vehicles.getCount(); j++) {
            Vehicle& vehicleB = vehicles[j];
            float lengthSquaredBetweenVehicles = vehicleA.getCenter().getLengthSquaredTo(vehicleB.getCenter());
            if (lengthSquaredBetweenVehicles > maxVehicleCollisionLengthSquared) continue;
            calculateBodyPlanesIfNeed(vehicleA);
            calculateBodyPlanesIfNeed(vehicleB);
            _anyCollisionsFound |= findCollisionDepth(vehicleA, vehicleB) || findCollisionDepth(vehicleB, vehicleA);
        }
    }
}

void VehiclesCollisionLogic::calculateBodyPlanesIfNeed(Vehicle& vehicle) {
    if (!_calculatedBodyPlanesCache[vehicle.getId()]) {
        vehicle.getBody().calculateTopTruncatedPlane();
        vehicle.getBody().calculateBottomTruncatedPlane();
        vehicle.getBody().calculateSideTruncatedPlanes();
        _calculatedBodyPlanesCache[vehicle.getId()] = true;
    }
}

bool VehiclesCollisionLogic::findCollisionDepth(Vehicle& vehicleA, Vehicle& vehicleB) {
    // vehicleA - машинка которая ударилась в vehicleB
    // vehicleB - машинка в которую ударилась vehicleA
    Body& vehicleABody = vehicleA.getBody();
    Body& vehicleBBody = vehicleB.getBody();
    Vector3 vehicleACollisionPointTo;
    int vehicleACollisionPointIndex;
    if (!hasCollision(vehicleABody, vehicleBBody, output vehicleACollisionPointTo, output vehicleACollisionPointIndex)) return false;
    Vector3 vehicleACollisionPointFrom = vehicleABody.getOppositeDiagonalPointFor(vehicleACollisionPointIndex);

    Collection<TruncatedPlane>& vehicleBSidePlanes = vehicleBBody.getSideTruncatedPlanes();
    for (int i = 0; i < vehicleBSidePlanes.getCount(); i++) {
        if (findCollisionDepthForBodySide(
            vehicleA.getId(), vehicleB.getId(), vehicleBSidePlanes[i], vehicleACollisionPointFrom, vehicleACollisionPointTo)) {
            return true;
        }
    }

    if (findCollisionDepthForBodySide(
        vehicleA.getId(), vehicleB.getId(), vehicleBBody.getTopTruncatedPlane(), vehicleACollisionPointFrom, vehicleACollisionPointTo)) {
        return true;
    }

    if (!vehicleB.allWheelsHaveGroundContact() &&
        findCollisionDepthForBodySide(
            vehicleA.getId(), vehicleB.getId(), vehicleBBody.getBottomTruncatedPlane(), vehicleACollisionPointFrom, vehicleACollisionPointTo)) {
        return true;
    }

    // если точка пересечения точно лежит на стороне кузова, в findCollisionDepthForBodySide collisionDepth равен нулевому вектору
    // то в итоге считаем что пересечения нет, хотя hasCollision выше показал что оно есть
    return false;
}

bool VehiclesCollisionLogic::hasCollision(
    Body& vehicleABody, Body& vehicleBBody, output Vector3& vehicleACollisionPoint, output int& vehicleACollisionPointIndex) {
    Collection<Vector3*>& vehicleABodyPoints = vehicleABody.getPoints();
    for (int pointIndex = 0; pointIndex < vehicleABodyPoints.getCount(); pointIndex++) {
        if (vehicleBBody.isPointInside(*vehicleABodyPoints[pointIndex])) {
            vehicleACollisionPoint = *vehicleABodyPoints[pointIndex];
            vehicleACollisionPointIndex = pointIndex;
            return true;
        }
    }

    return false;
}

bool VehiclesCollisionLogic::findCollisionDepthForBodySide(int vehicleAId, int vehicleBId, Plane& vehicleBPlane, Vector3 rayFrom, Vector3 rayTo) {
    Vector3 _;
    if (!vehicleBPlane.hasCollision(rayFrom, rayTo, 0.01f, output _)) return false;
    Vector3 collisionPoint = vehicleBPlane.getProjectedPoint(rayTo);
    Vector3 collisionDepth = rayTo.getDirectionTo(collisionPoint);
    if (collisionDepth.isZero()) return false;
    VehicleCollisionInfo& collisionInfo = _collisionInfo[vehicleAId];
    collisionInfo.collisionPoints.add(collisionPoint);
    collisionInfo.collisionDepths.add(collisionDepth);
    collisionInfo.anotherVehicleId.add(vehicleBId);

    return true;
}
