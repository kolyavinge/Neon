#include <model/common.h>

Angles::Angles() {
    init();
}

void Angles::init() {
    yaw = 0.0f;
    pitch = 0.0f;
    roll = 0.0f;
}

Measures::Measures() {
    xLength = 0.0f;
    yLength = 0.0f;
    zLength = 0.0f;
}
