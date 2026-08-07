#include <lib/calc/Math.h>
#include <model/vehicle/Spring.h>

Spring::Spring() {
    _stiffness = 0.0f;
    _damperCompression = 0.0f;
    _damperRebound = 0.0f;
    _bumpStopStiffness = 0.0f;
    _minLength = 0.0f;
    _maxLength = 0.0f;
    //_maxWeight = 0.0f;
    _prevLength = 0.0f;
    _currentLength = 0.0f;
    _springForce = 0.0f;
    _antiRollForce = 0.0f;
}

void Spring::init(WheelPosition position, Vector3 wheelFrontNormal, Vector3 wheelOutsideNormal) {
    bool isFrontWheel = position == WheelPosition::frontLeft || position == WheelPosition::frontRight;
    if (isFrontWheel) {
        _stiffness = _data.frontSpringStiffness;
        _damperCompression = _data.frontSpringDamperCompression;
        _damperRebound = _data.frontSpringDamperRebound;
        _minLength = _data.frontSpringMinLength;
        _maxLength = _data.frontSpringMaxLength;
        //_maxWeight = _data.frontSpringMaxWeight;
    } else {
        _stiffness = _data.rearSpringStiffness;
        _damperCompression = _data.rearSpringDamperCompression;
        _damperRebound = _data.rearSpringDamperRebound;
        _minLength = _data.rearSpringMinLength;
        _maxLength = _data.rearSpringMaxLength;
        //_maxWeight = _data.rearSpringMaxWeight;
    }
    _bumpStopStiffness = _data.springBumpStopStiffness;
    _initPosition.setZero();
    if (isFrontWheel) {
        _initPosition.addMultiplied(wheelFrontNormal, _data.frontWheelLengthToMassCenter);
        _initPosition.addMultiplied(wheelOutsideNormal, _data.frontTrackWidth / 2.0f);
    } else {
        _initPosition.subMultiplied(wheelFrontNormal, _data.rearWheelLengthToMassCenter);
        _initPosition.addMultiplied(wheelOutsideNormal, _data.rearTrackWidth / 2.0f);
    }
    _initPosition.addMultiplied(CommonConstants::upAxis, 0.1f);
    _position.setZero();
    _prevLength = _maxLength;
    _currentLength = _prevLength;
}

float Spring::getMinLength() {
    return _minLength;
}

float Spring::getMaxLength() {
    return _maxLength;
}

Vector3 Spring::getPosition() {
    return _position;
}

float Spring::getLength() {
    return _currentLength;
}

float Spring::getSpringForce() {
    return _springForce;
}

float Spring::getAntiRollForce() {
    return _antiRollForce;
}

void Spring::setAntiRollForce(float force) {
    _antiRollForce = force;
}

//void Spring::calculateLength(float wheelLoadWeight) {
//    _prevLength = _currentLength;
//    _currentLength = _maxLength - _maxLength * (wheelLoadWeight / _maxWeight);
//    _currentLength = Numeric::clamp(_currentLength, _minLength, _maxLength);
//}

void Spring::calculateLength(Vector3 wheelCenter) {
    _prevLength = _currentLength;
    _currentLength = _position.getLengthTo(wheelCenter);
    _currentLength = Numeric::clamp(_currentLength, _minLength, _maxLength);
}

void Spring::calculateSpringForce(float dt) {
    float depth = _maxLength - _currentLength;
    float speed = (_prevLength - _currentLength) / dt;
    float damper = _currentLength < _prevLength ? _damperCompression : _damperRebound;
    _springForce = _stiffness * depth + damper * speed;
    float compressionPercent = depth / _maxLength;
    if (compressionPercent > 0.85f) {
        _springForce += _bumpStopStiffness * (depth - (_maxLength * 0.85f));
    }
    if (_springForce < 0.0f) _springForce = 0.0f;
}

void Spring::calculatePosition(TransformMatrix4& vehicleModelMatrix) {
    _position = vehicleModelMatrix.mulPoint(_initPosition);
}
