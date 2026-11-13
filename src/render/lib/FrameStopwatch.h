#pragma once

#include <lib/system.h>
#include <render/lib/opengl.h>

class FrameStopwatch : public Object {

    int _prevFrame;
    int _currentFrame;
    GLuint _queryId[2];

public:
    int renderTimeMsc;

    FrameStopwatch();
    void beginFrame();
    void endFrame();
};
