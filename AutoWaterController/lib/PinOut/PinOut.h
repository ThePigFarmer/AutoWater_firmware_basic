/*
  name: PinOut.h
  category: pin control
*/

#ifndef PIN_OUT_h
#define PIN_OUT_h

#include "Arduino.h"

class PinOut
{
public:
  PinOut(bool isInverted = 0);
  bool status();
  void begin(uint8_t pin);
  void off();
  void on();
  void toggle();
  void write(bool value);

private:
  bool _isInverted;
  bool _state;
  bool _value;
  uint8_t _pin;
};
#endif