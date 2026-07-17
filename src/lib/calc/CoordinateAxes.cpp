#include <lib/calc/CoordinateAxes.h>

void CoordinateAxes::setAxes(Vector3 rightAxis, Vector3 frontAxis) {
    _initRightAxis = rightAxis;
    _initFrontAxis = frontAxis;
    _rightAxis = rightAxis;
    _frontAxis = frontAxis;
    _upAxis = _rightAxis;
    _upAxis.vectorProduct(_frontAxis);
    _upAxis.normalize();
}

Vector3 CoordinateAxes::getRightAxis() {
    return _rightAxis;
}

Vector3 CoordinateAxes::getFrontAxis() {
    return _frontAxis;
}

Vector3 CoordinateAxes::getUpAxis() {
    return _upAxis;
}

void CoordinateAxes::rotate(TransformMatrix4 m) {
    _rightAxis = m.mul(_initRightAxis, 0.0f);
    _frontAxis = m.mul(_initFrontAxis, 0.0f);
    _rightAxis.normalize();
    _frontAxis.normalize();
    _upAxis = _rightAxis;
    _upAxis.vectorProduct(_frontAxis);
    _upAxis.normalize();
}
