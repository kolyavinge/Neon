#include <common/constants.h>
#include <model/vehicle/Chassis.h>

Chassis::Chassis() {
    init();
}

void Chassis::init() {
    _frontNormal.set(0.0f, 1.0f, 0.0f);
    _rightNormal.set(1.0f, 0.0f, 0.0f);
    _topNormal = CommonConstants::upVector;
    _angles.init();
}

Vector3& Chassis::getFrontNormal() {
    return _frontNormal;
}

void Chassis::setFrontNormal(Vector3& frontNormal) {
    _frontNormal = frontNormal;
}

Vector3& Chassis::getRightNormal() {
    return _rightNormal;
}

void Chassis::setRightNormal(Vector3& rightNormal) {
    _rightNormal = rightNormal;
}

Vector3& Chassis::getTopNormal() {
    return _topNormal;
}

void Chassis::setTopNormal(Vector3& topNormal) {
    _topNormal = topNormal;
}

Angles& Chassis::getAngles() {
    return _angles;
}
