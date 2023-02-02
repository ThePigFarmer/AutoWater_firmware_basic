#define between(x, a, b) (((a) <= (x)) && ((x) <= (b)))

#include <Arduino.h>
#include "config.h"
#include <Wire.h>
#include <EEPROM.h>
#include <BtButton.h>
#include "TimeCalc.h"

BtButton bnt(BUTTON_PIN);
TimeCalc timeCalc;

struct Valve1
{
    uint16_t startTimes[4] = {540};
    uint16_t endTimes[4] = {660};
};

struct Valve2
{
    uint16_t startTimes[4] = {};
    uint16_t endTimes[4] = {};
};

struct Valve3
{
    uint16_t startTimes[4] = {};
    uint16_t endTimes[4] = {};
};

struct Valve4
{
    uint16_t startTimes[4] = {};
    uint16_t endTimes[4] = {};
};

struct Valves
{
    struct Valve1 v1;
    struct Valve2 v2;
    struct Valve3 v3;
    struct Valve4 v4;
}; // 64 bytes
Valves valves;

void loadValveData();
void saveValveData();
void runValves(uint8_t minutes);
void intiValvePins();
void test();

void setup()
{
    Serial.begin(115200);
    Wire.begin(); // for DS3231
    Serial.print("Serial and I2C started\n");

    // loadValveData();
} // end setup

void loop()
{
    // input ------------------------------------
    bnt.read();
    char *const timeStr = timeCalc.getTimeStr();

    // proccess ---------------------------------

    // press for eeprom write
    if (bnt.changedToPressed())
    {
        saveValveData();
    }

    // output -----------------------------------
    runValves(timeCalc.minute());
    Serial.println(timeCalc.minute());
} // end loop

// functions --------------------------------------------------------------------------------------

void loadValveData()
{
    EEPROM.get(0, valves);
}

void saveValveData()
{
    digitalWrite(LED_BUILTIN, 1);
    EEPROM.put(0, valves);
    delay(250);
    digitalWrite(LED_BUILTIN, 0);
    delay(250);
}

// run valves - not very DRY
void runValves(uint8_t minutes)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        if (between(minutes, valves.v1.startTimes[i], valves.v1.endTimes[i]))
            digitalWrite(V1_PIN, HIGH);
        else
            digitalWrite(V1_PIN, LOW);

        if (between(minutes, valves.v2.startTimes[i], valves.v2.endTimes[i]))
            digitalWrite(V2_PIN, HIGH);
        else
            digitalWrite(V2_PIN, LOW);

        if (between(minutes, valves.v3.startTimes[i], valves.v3.endTimes[i]))
            digitalWrite(V3_PIN, HIGH);
        else
            digitalWrite(V3_PIN, LOW);

        if (between(minutes, valves.v4.startTimes[i], valves.v4.endTimes[i]))
            digitalWrite(V4_PIN, HIGH);
        else
            digitalWrite(V4_PIN, LOW);
    }
}

void initValvePins()
{
    pinMode(V1_PIN, OUTPUT);
    pinMode(V2_PIN, OUTPUT);
    pinMode(V3_PIN, OUTPUT);
    pinMode(V4_PIN, OUTPUT);
}