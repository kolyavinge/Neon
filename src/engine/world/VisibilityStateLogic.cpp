#include <engine/world/VisibilityStateLogic.h>
#include <lib/calc/Math.h>

VisibilityState VisibilityStateLogic::getStateForWorldSegment(WorldSegment& segment, Camera& camera) {
    Rect2d& boundaryBox = segment.getBoundaryBox();
    float lengthSquared =
        Math::min(
            Math::min(boundaryBox.downLeft.getLengthSquaredTo(camera.getPosition()), boundaryBox.downRight.getLengthSquaredTo(camera.getPosition())),
            Math::min(boundaryBox.upLeft.getLengthSquaredTo(camera.getPosition()), boundaryBox.upRight.getLengthSquaredTo(camera.getPosition())));
    if (lengthSquared > 500.0f * 500.0f) return VisibilityState::shape;
    if (lengthSquared > 400.0f * 400.0f) return VisibilityState::low;
    if (lengthSquared > 200.0f * 200.0f) return VisibilityState::medium;
    return VisibilityState::high;
}

VisibilityState VisibilityStateLogic::getStateForVehicle(Vehicle& vehicle, Camera& camera) {
    float lengthSquared = vehicle.getCenter().getLengthSquaredTo(camera.getPosition());
    if (lengthSquared > 400.0f * 400.0f) return VisibilityState::shape;
    if (lengthSquared > 200.0f * 200.0f) return VisibilityState::low;
    if (lengthSquared > 50.0f * 50.0f) return VisibilityState::medium;
    return VisibilityState::high;
}
