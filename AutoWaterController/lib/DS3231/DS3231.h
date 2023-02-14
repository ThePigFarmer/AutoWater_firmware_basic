#pragma once

#include <Arduino.h>
#include <Wire.h>

// DS3231 I2C Addresses - hardwired in IC
#define DS3231_READ 0xD1
#define DS3231_WRITE 0xD0
#define DS3231_ADDR 0x68

// DS3231 Registers
#define DS3231_SECONDS 0x00
#define DS3231_MINUTES 0x01
#define DS3231_HOURS 0x02
#define DS3231_DAY 0x03
#define DS3231_DATE 0x04
#define DS3231_CEN_MONTH 0x05
#define DS3231_DEC_YEAR 0x06
#define DS3231_ALARM1_SECONDS 0x07
#define DS3231_ALARM1_MINUTES 0x08
#define DS3231_ALARM1_HOURS 0x09
#define DS3231_ALARM1_DAY_DATE 0x0a
#define DS3231_ALARM2_MINUTES 0x0b
#define DS3231_ALARM2_HOURS 0x0c
#define DS3231_ALARM2_DAY_DATE 0x0d
#define DS3231_CONTROL 0x0e
#define DS3231_CTL_STATUS 0x0f
#define DS3231_AGING_OFFSET 0x10
#define DS3231_TEMP_MSB 0x11
#define DS3231_TEMP_LSB 0x12

class Date
{
public:
    uint16_t year;
    uint8_t month;
    uint8_t day;
};

class Time
{
public:
    uint16_t hour;
    uint8_t min;
    uint8_t sec;
};

class DS3231
{
public:
    Date getDate();
    Time getTime();
    void setDate(uint16_t year, uint8_t month, uint8_t day);
    void setTime(uint16_t hour, uint8_t min, uint8_t sec);

private:
    uint8_t bcd2bin(uint8_t num);
};