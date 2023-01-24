#include <Arduino.h>
#include <Valve.h>
#include <Wire.h>
#include <DS3231.h>

uint8_t valve1[2][8]
{

	{},
	{},
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
