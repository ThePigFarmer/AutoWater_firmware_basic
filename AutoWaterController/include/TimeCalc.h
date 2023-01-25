#include <Arduino.h>
#include <DS3231.h>

RTClib myRTC;

class TimeCalc
{
public:
    uint8_t refresh();
};