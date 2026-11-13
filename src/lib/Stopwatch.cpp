#include <lib/DateTime.h>
#include <lib/Stopwatch.h>

Stopwatch::Stopwatch() {
    _elapsedMilliseconds = 0;
    _startTimestamp = 0;
    _lastTimestamp = 0;
    _isActive = false;
}

void Stopwatch::start() {
    if (!_isActive) {
        _startTimestamp = DateTime::getCurrentEpochMilliseconds();
        _isActive = true;
    }
}

void Stopwatch::stop() {
    if (_isActive) {
        commitElapsed();
        _isActive = false;
    }
}

void Stopwatch::reset() {
    _elapsedMilliseconds = 0;
    _startTimestamp = DateTime::getCurrentEpochMilliseconds();
}

void Stopwatch::restart() {
    reset();
    start();
}

long long Stopwatch::getElapsedMilliseconds() {
    return _elapsedMilliseconds;
}

TimeSpan Stopwatch::getElapsed() {
    if (_isActive) {
        commitElapsed();
    }

    return TimeSpan(_elapsedMilliseconds);
}

void Stopwatch::commitElapsed() {
    _lastTimestamp = DateTime::getCurrentEpochMilliseconds();
    _elapsedMilliseconds += _lastTimestamp - _startTimestamp;
    _startTimestamp = _lastTimestamp;
}
