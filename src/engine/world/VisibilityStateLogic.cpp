#include <engine/world/VisibilityStateLogic.h>

VisibilityState VisibilityStateLogic::getStateForWorldSegment(WorldSegment& segment, Camera& camera) {
    float lengthSquared = segment.getBoundaryBox().getNearestLengthSquaredTo(camera.getPosition());
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
