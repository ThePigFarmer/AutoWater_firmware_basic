#include <TimeCalc.h>

uint8_t TimeCalc::minute()
{
    // convert to minuets
    DateTime now = rtcNow.now();

    uint8_t mins = now.hour() * 60 + now.minute();
    return mins;
}

char const *getTimeStr()
{
    DateTime now = rtcNow.now();
    char timeBuffer[8];
    sprintf(timeBuffer, "%u:%u:%u", now.hour(), now.minute(), now.second());
    return timeBuffer;
}