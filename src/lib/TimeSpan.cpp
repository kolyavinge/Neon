#include <lib/TimeSpan.h>

TimeSpan::TimeSpan() {
    _milliseconds = 0;
    _seconds = 0;
    _minutes = 0;
    _hours = 0;
}

TimeSpan::TimeSpan(long long totalMilliseconds) {
    initFromMilliseconds(totalMilliseconds);
}

int TimeSpan::getHours() {
    return _hours;
}

int TimeSpan::getMinutes() {
    return _minutes;
}

int TimeSpan::getSeconds() {
    return _seconds;
}

int TimeSpan::getMilliseconds() {
    return _milliseconds;
}

void TimeSpan::initFromMilliseconds(long long totalMilliseconds) {
    _milliseconds = totalMilliseconds % 1000;
    _seconds = (totalMilliseconds / 1000) % 60;
    _minutes = (totalMilliseconds / (long long)(60 * 1000)) % 60;
    _hours = (totalMilliseconds / (long long)(60 * 60 * 1000)) % 60;
}
