/*
  PinOut.cpp
  category: pin control
*/

#include "Arduino.h"
#include "PinOut.h"

PinOut::PinOut(bool isInverted)
{
  _isInverted = isInverted;
  _state = 0;
};

bool PinOut::status()
{
  return _state;
}

void PinOut::begin(uint8_t pin)
{
  _pin = pin;
  pinMode(_pin, 1);
  digitalWrite(_pin, 0 ^ _isInverted);
}

void PinOut::off()
{
  _state = 0;
  digitalWrite(_pin, _state ^ _isInverted);
}

void PinOut::on()
{
  _state = 1;
  digitalWrite(_pin, _state ^ _isInverted);
}

void PinOut::toggle()
{
  _state = !_state;
  digitalWrite(_pin, _state ^ _isInverted);
}

void PinOut::write(bool value)
{
  _state = value;
  digitalWrite(_pin, _state ^ _isInverted);
}