#pragma once

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFiClient.h>

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

class MqttHandler
{
public:
    void setup();
    void loop();
    void refresh();
    void reconnect();

private:
    const char *mqttServer = "broker.hivemq.com";
    int mqttPort = 1883;

    void callback(char *topic, byte *message, unsigned int length);
};