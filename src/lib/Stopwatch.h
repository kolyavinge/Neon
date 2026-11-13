#pragma once

#include <lib/TimeSpan.h>
#include <lib/system.h>

class Stopwatch : public Object {

    long long _elapsedMilliseconds;
    long long _startTimestamp;
    long long _lastTimestamp;
    bool _isActive;

public:
    Stopwatch();

    void start();
    void stop();
    void reset();
    long long getElapsedMilliseconds();
    TimeSpan getElapsed();

private:
    void commitElapsed();
};
