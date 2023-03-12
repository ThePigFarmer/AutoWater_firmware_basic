#define between(x, a, b) (((a) <= (x)) && ((x) <= (b)))

#include <Arduino.h>
#include "config.h"
#include <Wire.h>
#include <EEPROM.h>
#include <BtButton.h>
#include <DS3231.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

BtButton bnt(BUTTON_PIN);
DS3231 rtc;
Time t;

const char *ssid = "ssid";
const char *password = "password";
const uint16_t port = 8090;
const char *host = "192.168.83";

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
    delay(500);
    Wire.begin(); // for DS3231
    delay(500);
    Serial.print("Serial and I2C started\n");

    WiFi.mode(WIFI_STA); // Optional
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());

    // loadValveData(); // not for testing
} // end setup

void loop()
{
    WiFiClient client;

    if (!client.connect(host, port))
    {
        Serial.println(F("host conn failed"));
        delay(1000);
        return;
    }

    Serial.println("conn succ");
    client.print("hello from esp");
    client.stop();

    delay(10000);

    // timed loop
    if ((millis() - prevMillis) > timer1)
    {
        prevMillis = millis();

        t = rtc.getTime(); // read DS3231 registers at once

        uint16_t minutesSinceMidnight = t.hour * 60 + t.min;

        runValves(minutesSinceMidnight);
        Serial.println(minutesSinceMidnight);

        Serial.println(F("\n"));
    } // end timed loop

    bnt.read();

    if (bnt.changed())
    {
        // press for eeprom write
        if (bnt.isPressed())
        {
            saveValveData();
            Serial.println(F("Saved valves to EEPROM"));
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
    EEPROM.put(0, valves);
}

// run valves - not very DRY
void runValves(uint8_t minutes)
{
    loadValveData();
    bool exitLoop;

    // valve 1
    exitLoop = false;
    for (uint8_t i = 0; i < 4; i++)
    {
        if (between(minutes, valves.v1.startTimes[i], valves.v1.endTimes[i]))
        {
            digitalWrite(V1_PIN, HIGH);
            exitLoop = true;
        }
        else
        {
            digitalWrite(V1_PIN, LOW);
        }

        if (exitLoop)
            break;
    }

    // valve 2
    exitLoop = false;
    for (uint8_t i = 0; i < 4; i++)
    {
        if (between(minutes, valves.v2.startTimes[i], valves.v2.endTimes[i]))
        {
            digitalWrite(V2_PIN, HIGH);
            exitLoop = true;
        }
        else
        {
            digitalWrite(V2_PIN, LOW);
        }

        if (exitLoop)
            break;
    }

    // valve 3
    exitLoop = false;
    for (uint8_t i = 0; i < 4; i++)
    {
        if (between(minutes, valves.v3.startTimes[i], valves.v3.endTimes[i]))
        {
            digitalWrite(V3_PIN, HIGH);
            exitLoop = true;
        }
        else
        {
            digitalWrite(V3_PIN, LOW);
        }

        if (exitLoop)
            break;
    }

    // valve 4
    exitLoop = false;
    for (uint8_t i = 0; i < 4; i++)
    {
        if (between(minutes, valves.v4.startTimes[i], valves.v4.endTimes[i]))
        {
            digitalWrite(V4_PIN, HIGH);
            exitLoop = true;
        }
        else
        {
            digitalWrite(V4_PIN, LOW);
        }

        if (exitLoop)
            break;
    }
}

void initValvePins()
{
    pinMode(V1_PIN, OUTPUT);
    pinMode(V2_PIN, OUTPUT);
    pinMode(V3_PIN, OUTPUT);
    pinMode(V4_PIN, OUTPUT);
}
