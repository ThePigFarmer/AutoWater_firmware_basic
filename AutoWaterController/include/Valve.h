/*
  Valve.h
*/

#ifndef VALVE_h
#define VALVE_h

#include <Arduino.h>

#ifndef between
#define between(x, a, b) (((a) <= (x)) && ((x) <= (b)))
#endif

class Valve
{
public:
  Valve(uint8_t pin);
  bool shouldRun();
  void write(bool targetState);
  void setTimes(uint8_t startHour, uint8_t startMin, uint8_t endHour, uint8_t endMin);

private:
  uint32_t _start;
  uint32_t _end;
};

#endif