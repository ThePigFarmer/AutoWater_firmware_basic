#include <Arduino.h>
#include <Valve.h>
#include <Wire.h>
#include <DS3231.h>

Valve v(13);

void setup()
{
    Serial.begin(115200);
    Wire.begin();
    v.setTimes(4, 4, 21, 4);
}

void loop()
{
    v.write(v.shouldRun());
}
