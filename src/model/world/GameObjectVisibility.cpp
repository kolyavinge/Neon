#include <model/vehicle/VehicleLights.h>
#include <model/world/GameObjectVisibility.h>

GameObjectVisibility::GameObjectVisibility() {
    _camera = nullptr;
    _segmentCollection = nullptr;
    _vehicles = nullptr;
}

void GameObjectVisibility::init(WorldSegmentCollection& segmentCollection, Collection<Vehicle>& vehicles, int allSegmentsCount) {
    _segmentCollection = &segmentCollection;
    _vehicles = &vehicles;
    // макс кол-во видимых сегментов не может быть больше половины всех сегментов
    visibleSegments.prepareEnoughCapacity(allSegmentsCount / 2);
    visibleSegmentStates.prepareEnoughCapacity(allSegmentsCount / 2);
    visibleSegmentStates.initAll(VisibilityState::high);
    vehicleVisibilityStates.initAll(VisibilityState::high);
}

void GameObjectVisibility::setCamera(Camera& camera) {
    _camera = &camera;
}

Collection<WorldSegment*>& GameObjectVisibility::getVisibleSegments() {
    return visibleSegments;
}

VisibilityState GameObjectVisibility::getSegmentVisibilityState(int segmentIndex) {
    return visibleSegmentStates[segmentIndex];
}

VisibilityState GameObjectVisibility::getVehicleVisibilityState(Vehicle& vehicle) {
    return vehicleVisibilityStates[vehicle.getId()];
}

Collection<Light*>& GameObjectVisibility::getLightsForSegment(WorldSegment& segment) {
    _lightsWithoutSpecular.clear();
    _lightsResultTmp.clear();

    // источники света в сегменте
    _lightsResultTmp.addRange(segment.getLights());

    // свет других машинок достающих до сегмента
    float maxLightDistanceSquared = _vehicles->first().getLights().getFrontLeftLight().getMaxDistanceSquared();
    for (int i = 0; i < _vehicles->getCount(); i++) {
        Vehicle& vehicle = (*_vehicles)[i];
        VehicleLights& vehicleLights = vehicle.getLights();
        bool vehicleLightsAffectToSegment =
            segment.getBoundaryBox().getNearestLengthSquaredTo(vehicleLights.getFrontCenter()) < maxLightDistanceSquared ||
            segment.getCenter().getLengthSquaredTo(vehicleLights.getFrontCenter()) < maxLightDistanceSquared;
        if (!vehicleLightsAffectToSegment) continue;
        // нет смысла считать specular от фар, если они смотрят туда же куда камера, машинка перекроет собой это световое пятно
        bool isSpecularEnabled = _camera->getLookDirection().dotProduct(vehicle.getChassisFrontNormal()) < 0.9f;
        if (isSpecularEnabled) {
            _lightsResultTmp.add(&vehicleLights.getFrontLeftLight());
            _lightsResultTmp.add(&vehicleLights.getFrontRightLight());
        } else {
            // выключаем specular для левой фары
            Light* light = &_lightsWithoutSpecular.addNew();
            *light = vehicleLights.getFrontLeftLight();
            light->enableSpecular(false);
            _lightsResultTmp.add(light);
            // и для правой
            light = &_lightsWithoutSpecular.addNew();
            *light = vehicleLights.getFrontRightLight();
            light->enableSpecular(false);
            _lightsResultTmp.add(light);
        }
    }

    return _lightsResultTmp;
}

Collection<Light*>& GameObjectVisibility::getLightsForVehicle(Vehicle& vehicle) {
    _lightsResultTmp.clear();
    WorldSegment& vehicleSegment = _segmentCollection->getWorldSegmentForPoint(vehicle.getCenter());

    // источники света в сегменте, в котором находится машинка
    _lightsResultTmp.addRange(vehicleSegment.getLights());

    // свет самой машинки. передние фары
    bool vehicleLightsLookToCamera = _camera->getLookDirection().dotProduct(vehicle.getChassisFrontNormal()) < 0.0f;
    if (vehicleLightsLookToCamera) {
        // результат действия света виден, только если фары обращены в камеру
        _lightsResultTmp.add(&vehicle.getLights().getFrontLeftLight());
        _lightsResultTmp.add(&vehicle.getLights().getFrontRightLight());
    }

    // свет самой машинки. задние фары
    if (vehicle.getLights().isRearBrakeLightActive()) {
        _lightsResultTmp.add(&vehicle.getLights().getRearBrakeLight());
    }
    _lightsResultTmp.add(&vehicle.getLights().getRearLeftSideLight());
    _lightsResultTmp.add(&vehicle.getLights().getRearRightSideLight());

    // свет других машинок достающих до этой
    float maxDistanceLengthSquared = vehicle.getLights().getFrontLeftLight().getMaxDistanceSquared();
    for (int i = 0; i < _vehicles->getCount(); i++) {
        Vehicle& otherVehicle = (*_vehicles)[i];
        if (vehicle.getId() == otherVehicle.getId()) continue;
        if (vehicle.getCenter().getLengthSquaredTo(otherVehicle.getLights().getFrontCenter()) < maxDistanceLengthSquared) {
            _lightsResultTmp.add(&otherVehicle.getLights().getFrontLeftLight());
            _lightsResultTmp.add(&otherVehicle.getLights().getFrontRightLight());
        }
    }

    return _lightsResultTmp;
}
