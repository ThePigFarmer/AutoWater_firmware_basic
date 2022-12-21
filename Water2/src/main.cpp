#include <Arduino.h>
#include <DS3231.h>

RTClib rtcNow;

void setup()
{
	Serial.begin(115200);
//!AutoWater_Valve_Init

//!end


}

void loop()
{
	DateTime now = rtcNow.now();
	uint32_t minuets = now.hour() * 60 + now.minuet();
	
//!AutoWater_Valve_Loop

//!end
}
