#pragma once
#include <Arduino.h>
#include <DS3231.h>

class TimeCalc
{
public:
    RTClib rtcNow;
    DS3231 rtc;
    uint8_t minute();
    char timeStr();
};