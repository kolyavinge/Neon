#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>

class Camera : public Object {

    Vector3 _position;
    Vector3 _lookDirection;
    float _verticalViewAngle;
    TransformMatrix4 _viewMatrix;
    TransformMatrix4 _projectionMatrix;

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
    void calculateViewMatrix();
    void calculateProjectionMatrix();
};
