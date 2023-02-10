#define between(x, a, b) (((a) <= (x)) && ((x) <= (b)))

#include <Arduino.h>
#include "config.h"
#include <Wire.h>
#include <EEPROM.h>
#include <BtButton.h>
#include <DS3231.h>

BtButton bnt(BUTTON_PIN);
DS3231 ds3231rtc;
RTClib rtc;
DateTime now;

uint32_t prevMillis;
const uint16_t timer1 = 1000;

struct Valve1
{
    uint16_t startTimes[4] = {0};
    uint16_t endTimes[4] = {1};
};

struct Valve2
{
    uint16_t startTimes[4] = {1};
    uint16_t endTimes[4] = {2};
};

struct Valve3
{
    uint16_t startTimes[4] = {2};
    uint16_t endTimes[4] = {3};
};

struct Valve4
{
    uint16_t startTimes[4] = {3};
    uint16_t endTimes[4] = {4};
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
    Serial.begin(MONITOR_SPEED);
    Wire.begin(); // for DS3231
    Serial.print("Serial and I2C started\n");

    // loadValveData(); // not for testing
} // end setup

void loop()
{
    if ((millis() - prevMillis) > timer1)
    {
        prevMillis = millis();

        // time
        DateTime now = rtc.now();

        // minutes since midnight
        uint8_t minutesSinceMidnight = now.hour() * 60 + now.minute();

        runValves(minutesSinceMidnight);
        Serial.println(minutesSinceMidnight);
    } // end timed loop

    bnt.read();

    if (bnt.changed())
    {
        // press for eeprom write
        if (bnt.isPressed())
        {
            saveValveData();
        }

        // hold for DS3231 time set
        if (bnt.isHeld())
        {
            ds3231rtc.setHour(0);
            ds3231rtc.setMinute(0);
            Serial.println(F("DS3231 time: 0:0:0"));
        }
    }
} // end main loop

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
    Serial.println(F("saved valves"));
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