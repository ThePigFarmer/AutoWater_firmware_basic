#pragma once

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFiClient.h>

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

class broker
{
public:
    void setup();
    void loop();
};