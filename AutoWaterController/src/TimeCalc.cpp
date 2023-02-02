#include <TimeCalc.h>

uint8_t TimeCalc::minute()
{
    // convert to minuets
    DateTime now = rtcNow.now();

    uint8_t mins = now.hour() * 60 + now.minute();
    return mins;
}

char TimeCalc::timeStr()
{
}