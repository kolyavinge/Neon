#pragma once

#include <lib/calc/Plane.h>
#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <model/vehicle/Vehicle.h>

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
    Vector3& getPosition();
    Vector3& getLookDirection();
    TransformMatrix4& getViewMatrix();
    TransformMatrix4& getProjectionMatrix();
    Plane& getFrustumPlane(FrustumPlanePosition position);
    void update(Vehicle& vehicle);

protected:
    void virtual innerUpdate(Vehicle& vehicle) = 0;
    void setVerticalViewAngle(float verticalViewAngle);
    void setPosition(Vector3& position);
    void setLookDirection(Vector3& lookDirection);

private:
    void calculateViewMatrix();
    void calculateProjectionMatrix();
    void calculateFrustumPlanes();
};
