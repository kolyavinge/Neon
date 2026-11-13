#pragma once

#include <lib/system.h>

class TimeSpan : public Object {

    int _hours;
    int _minutes;
    int _seconds;
    int _milliseconds;

public:
    TimeSpan();
    TimeSpan(long long totalMilliseconds);

    int getHours();
    int getMinutes();
    int getSeconds();
    int getMilliseconds();

    void initFromMilliseconds(long long totalMilliseconds);
};
