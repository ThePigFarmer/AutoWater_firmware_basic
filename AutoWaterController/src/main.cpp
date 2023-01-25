#include <Arduino.h>
#include <Wire.h>

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

Valve1 v1;
Valve2 v2;
Valve1 v3;
Valve2 v4;

void loadStructsFromEEPROM();
void putStructsInEEPROM();

void setup()
{
    Serial.begin(115200);
    Wire.begin(); // for DS3231
    Serial.print("Serial and I2C started\n");

    loadStructsFromEEPROM();
}

void loop()
{
}

void loadStructsFromEEPROM()
{
}

void putStructsInEEPROM()
{
    EEPROM.put(0, v1);
    EEPROM.put(4, v2);
    EEPROM.put(8, v3);
    EEPROM.put(12, v4);
}