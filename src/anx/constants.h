#pragma once

#include <lib/calc/Vector3.h>

class CommonConstants {

public:
    inline static const float screenAspect = 16.0f / 9.0f;
    inline static const float frameRate = 25.0f;
    inline static const float deltaTimeSec = 1.0f / frameRate;
    inline static const float g = 9.81f;
    inline static Vector3 axisOrigin = Vector3(0.0f, 0.0f, 0.0f);
    inline static Vector3 upVector = Vector3(0.0f, 0.0f, 1.0f);
};
