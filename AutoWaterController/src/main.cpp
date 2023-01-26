#include <Arduino.h>
#include <config.h>
#include <Wire.h>
#include <EEPROM.h>
#include <BtButton.h>

BtButton bnt(BUTTON_PIN);

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

struct Valves
{
    struct
    {
        Valve1 v1
    };
    struct
    {
        Valve2 v2
    };
    struct
    {
        Valve3 v3
    };
    struct
    {
        Valve4 v4
    };
};

Valves valves;

void loadValves();
void saveValves();

void setup()
{
    Serial.begin(115200);
    Wire.begin(); // for DS3231
    Serial.print("Serial and I2C started\n");

    loadValves();
} // end setup

void loop()
{
    // input ------------------------------------
    bnt.read();

    // proccess ---------------------------------
    if (bnt.changedToPress())
        saveValves();

    // output -----------------------------------
} // end loop

void loadValves(Valves &valves)
{
    EEPROM.get(0, valves);
}

void saveValves(Valves &valves)
{
    digitalWrite(LED_BUILTIN, 1);
    EEPROM.put(0, valves);
    digitalWrite(LED_BUILTIN, 0);
}