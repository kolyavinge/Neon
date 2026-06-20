#include <common/constants.h>
#include <engine/vehicle/WheelLogic.h>
#include <lib/calc/Math.h>

void WheelLogic::calculateNormalsBySteeringAngle(
    float steeringAngle,
    Vector3& chassisFrontNormal,
    Vector3& chassisTopNormal,
    output Vector3& newWheelFrontNormal,
    output Vector3& newLeftWheelOutsideNormal,
    output Vector3& newRightWheelOutsideNormal) {
    newWheelFrontNormal = Math::rotatePoint(chassisFrontNormal, steeringAngle, chassisTopNormal, CommonConstants::axisOrigin);
    newWheelFrontNormal.normalize();

    newLeftWheelOutsideNormal = Math::rotatePoint(chassisFrontNormal, steeringAngle + Math::piHalf, chassisTopNormal, CommonConstants::axisOrigin);
    newLeftWheelOutsideNormal.normalize();

    newRightWheelOutsideNormal = newLeftWheelOutsideNormal;
    newRightWheelOutsideNormal.mul(-1.0f);
}
