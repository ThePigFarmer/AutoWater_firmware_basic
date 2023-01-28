#include <TimeCalc.h>

uint8_t TimeCalc::minute()
{
    DateTime now = rtc.now();

    // convert to minuets
    uint8_t mins = now.hour() * 60 + now.minute();
    return mins;
}