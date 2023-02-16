#include <Broker.h>

char *mqttServer = "broker.hivemq.com";
int mqttPort = 1883;

void broker::setup()
{
    mqttClient.setServer(mqttServer, mqttPort);
    mqttClient.setCallback(callback);
}

void reconnect()
{
    Serial.println("Connecting to MQTT Broker...");
    while (!mqttClient.connected())
    {
        Serial.println("Reconnecting to MQTT Broker..");
        String clientId = "ESP32Client-";
        clientId += String(random(0xffff), HEX);

        if (mqttClient.connect(clientId.c_str()))
        {
            Serial.println("Connected.");
            // subscribe to topic
            mqttClient.subscribe("esp32/message");
        }
    }
}
