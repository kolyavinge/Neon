#pragma once

#include <lib/calc/UnitConverter.h>
#include <lib/calc/Vector3.h>

class CommonConstants {

public:
    inline static const char* title = "Neon";
    inline static const float screenAspect = 16.0f / 9.0f;
    inline static const int screenWidth = 1000;
    inline static const int screenHeight = (int)((float)screenWidth / screenAspect);
    inline static const float frameRate = 25.0f;
    inline static const float deltaTimeSec = 1.0f / frameRate;
    inline static const float g = 9.81f;
    inline static Vector3 axisOrigin = Vector3(0.0f, 0.0f, 0.0f);
    inline static Vector3 upVector = Vector3(0.0f, 0.0f, 1.0f);
    inline static const float verticalFieldOfViewDegrees = 45.0f;
    inline static const float verticalFieldOfView = UnitConverter::degreesToRadians(verticalFieldOfViewDegrees);
    inline static const float zNear = 0.01f;
    inline static const float zFar = 1000.0f;
};

class GameConstants {

public:
    inline static const int maxVehiclesCount = 1;
};
