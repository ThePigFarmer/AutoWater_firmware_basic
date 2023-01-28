#include <Arduino.h>
#include <DS3231.h>

RTClib rtc;

class TimeCalc
{
public:
    uint8_t minute();
};