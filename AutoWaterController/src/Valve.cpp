/*
  Valve.cpp
*/

#include <Arduino.h>
#include <DS3231.h>
#include <PinOut.h>
#include <Valve.h>

RTClib rtcNow;
PinOut valvePin;

Valve::Valve(uint8_t pin)
{
	valvePin.begin(pin);
}

void Valve::setTimes(uint8_t startHour, uint8_t startMin, uint8_t endHour, uint8_t endMin)
{
	_start = startHour * 60 + startMin;
	_end = endHour * 60 + endMin;
}

bool Valve::shouldRun()
{
	DateTime now = rtcNow.now();

	uint8_t hour = now.hour();
	uint8_t min = now.minute();

	uint32_t time = hour * 60 + min;

	bool x = (between(time, _start, _end)) ? true : false;
	// bool x = ((millis() / 1000) % 2);

	/*Serial.print(hour);
	Serial.print(F(":"));
	Serial.print(min);
	Serial.print(F("   time: "));
	Serial.print(time);
	Serial.print(F("   start: "));
	Serial.print(_start);
	Serial.print(F("   end: "));
	Serial.print(_end);
	Serial.print(F("   between: "));
	Serial.println(x);
	*/
	return x;
}

void Valve::write(bool targetState)
{
	valvePin.write(targetState);
}
