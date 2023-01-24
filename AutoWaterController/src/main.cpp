#include <Arduino.h>
#include <Valve.h>
#include <Wire.h>
#include <DS3231.h>

struct Valve1
{
    uint8_t startTimes[4] = {};
    uint8_t endTimes[4] = {};
};

struct Valve2
{
    uint8_t startTimes[4] = {};
    uint8_t endTimes[4] = {};
};

struct Valve3
{
    uint8_t startTimes[4] = {};
    uint8_t endTimes[4] = {};
};

struct Valve4
{
    uint8_t startTimes[4] = {};
    uint8_t endTimes[4] = {};
};

void setup()
{
    Serial.begin(115200);
    Wire.begin(); // for DS3231
    Serial.print("Serial and I2C started\n");
}

void loop()
{
}
