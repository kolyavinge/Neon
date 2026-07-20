#pragma once

#include <lib/calc/UnitConverter.h>
#include <lib/calc/Vector3.h>

class CommonConstants {

public:
    inline static const char* title = "Neon";
    inline static const float screenAspect = 16.0f / 9.0f;
    inline static const int screenWidth = 1000;
    inline static const int screenHeight = (int)((float)screenWidth / screenAspect);
    inline static const float frameRate = 60.0f;
    inline static const float deltaTimeSec = 1.0f / frameRate;
    inline static Vector3 axisOrigin = Vector3(0.0f, 0.0f, 0.0f);
    inline static Vector3 leftAxis = Vector3(-1.0f, 0.0f, 0.0f);
    inline static Vector3 rightAxis = Vector3(1.0f, 0.0f, 0.0f);
    inline static Vector3 frontAxis = Vector3(0.0f, 1.0f, 0.0f);
    inline static Vector3 upAxis = Vector3(0.0f, 0.0f, 1.0f);
    inline static const float verticalFieldOfViewDegrees = 45.0f;
    inline static const float verticalFieldOfView = UnitConverter::degreesToRadians(verticalFieldOfViewDegrees);
    inline static const float minPerspectiveDepth = 0.01f;
    inline static const float maxPerspectiveDepth = 1000.0f;
};

class PhysixConstants {

public:
    inline static const float g = 9.81f;
    inline static Vector3 gravityVector = Vector3(0.0f, 0.0f, -g);
};

class GameConstants {

public:
    inline static const int maxVehiclesCount = 1;
};

class VehicleConstants {

public:
    inline static Vector3 initChassisRightNormal = CommonConstants::rightAxis;
    inline static Vector3 initChassisFrontNormal = CommonConstants::frontAxis;
    inline static const int wheelsCount = 4;
    inline static const int driveWheelsCount = 2;
    inline static const int nonDriveWheelsCount = 2;
    inline static const float slipRatioLimit = 100.0f;
    inline static const float minLinearVelocityDelta = 0.1f;
    inline static const float minSlipAngleDelta = UnitConverter::degreesToRadians(0.5f);
};
