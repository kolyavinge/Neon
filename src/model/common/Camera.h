#pragma once

#include <lib/calc/Plane.h>
#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>

enum class FrustumPlanePosition {
    front = 0,
    left = 1,
    right = 2,
    _count
};

class Camera : public Object {

    Vector3 _position;
    Vector3 _lookDirection;
    float _verticalViewAngle;
    float _horizontalViewAngle;
    TransformMatrix4 _viewMatrix;
    TransformMatrix4 _projectionMatrix;
    Array<Plane, (int)FrustumPlanePosition::_count> _frustumPlanes;

public:
    Camera();
    float getVerticalViewAngle();
    void setVerticalViewAngle(float verticalViewAngle);
    Vector3& getPosition();
    void setPosition(Vector3& position);
    Vector3& getLookDirection();
    void setLookDirection(Vector3& lookDirection);
    TransformMatrix4& getViewMatrix();
    TransformMatrix4& getProjectionMatrix();
    Plane& getFrustumPlane(FrustumPlanePosition position);
    void calculateViewMatrix();
    void calculateProjectionMatrix();
    void calculateFrustumPlanes();
};
