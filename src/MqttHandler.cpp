#include <MqttHandler.h>

void MqttHandler::setup()
{
    mqttClient.setServer(mqttServer, mqttPort);
    mqttClient.setCallback(callback);
}

void MqttHandler::loop()
{
    if (!mqttClient.connected())
        reconnect();
    mqttClient.loop();

    mqttClient.publish("esp32/temperature", tempString);
}

void MqttHandler::reconnect()
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

void MqttHandler::callback(char *topic, byte *message, unsigned int length)
{
    Serial.print("Callback - ");
    Serial.print("Message:");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)message[i]);
    }
}