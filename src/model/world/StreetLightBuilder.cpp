#include <common/constants.h>
#include <lib/calc/Math.h>
#include <lib/calc/TransformMatrix4.h>
#include <model/common/Light.h>
#include <model/world/StreetLightBuilder.h>

StreetLightBuilder::StreetLightBuilder() {
    _resultPrimitives = nullptr;
    _resultObjects = nullptr;
    _groundPrimitives = nullptr;
    _kind = (WorldObjectKind)-1;
    _angle = 0.0f;
    _count = 1;
}

StreetLightBuilder& StreetLightBuilder::setWorldPrimitiveResultList(List<WorldPrimitive>& resultPrimitives) {
    _resultPrimitives = &resultPrimitives;
    return *this;
}

StreetLightBuilder& StreetLightBuilder::setWorldObjectResultList(List<WorldObject>& resultObjects) {
    _resultObjects = &resultObjects;
    return *this;
}

StreetLightBuilder& StreetLightBuilder::setGroundPrimitives(List<WorldPrimitive>& groundPrimitives) {
    _groundPrimitives = &groundPrimitives;
    return *this;
}

StreetLightBuilder& StreetLightBuilder::setKind(WorldObjectKind kind) {
    _kind = kind;
    return *this;
}

StreetLightBuilder& StreetLightBuilder::setPosition(Vector3 position) {
    _position = position;
    return *this;
}

StreetLightBuilder& StreetLightBuilder::setRotation(float angle) {
    _angle = angle;
    return *this;
}

StreetLightBuilder& StreetLightBuilder::setColor(float intensity, Vector3 color) {
    _color = color;
    _color.setLength(intensity);

    return *this;
}

StreetLightBuilder& StreetLightBuilder::setOffset(Vector3 offset) {
    _offset = offset;
    return *this;
}

StreetLightBuilder& StreetLightBuilder::setCount(int count) {
    _count = count;
    return *this;
}

StreetLightBuilder& StreetLightBuilder::build() {
    Array<Vector3, 1> boundaryPoints;
    for (int i = 0; i < _count; i++) {
        _position.z = getGroundZ(_position);
        boundaryPoints[0] = _position;
        Vector3 frontNormal = Math::rotatePoint(CommonConstants::frontAxis, _angle, CommonConstants::upAxis, CommonConstants::axisOrigin);
        WorldObject object(_kind, _position, boundaryPoints, frontNormal, CommonConstants::upAxis);

        TransformMatrix4 translate, rotate, translateAndRotate;
        translate.translate(_position.x, _position.y, _position.z);
        rotate.rotate(_angle, CommonConstants::upAxis);
        translateAndRotate = translate;
        translateAndRotate.mul(rotate);
        Vector3 lightPosition = translateAndRotate.mulPoint(WorldObjectData::getLightPositionFor(_kind));
        Vector3 lightDirection = rotate.mulVector(WorldObjectData::getLightDirectionFor(_kind));
        Light light;
        light.setPosition(lightPosition);
        light.setDirection(lightDirection);
        light.setColor(_color);
        object.setLight(light);
        _resultObjects->add(object);
        _position.add(_offset);
    }

    _count = 1;

    return *this;
}

float StreetLightBuilder::getGroundZ(Vector3 position) {
    Vector3 rayFrom = position, rayTo = position;
    rayFrom.z -= 2.0f;
    rayTo.z += 2.0f;
    Vector3 collisionPoint;
    for (int i = 0; i < _groundPrimitives->getCount(); i++) {
        WorldPrimitive& pr = (*_groundPrimitives)[i];
        if (pr.hasCollision(rayFrom, rayTo, 0.01f, output collisionPoint)) {
            return collisionPoint.z;
        }
    }
    Assert::fail();

    return 0.0f;
}
