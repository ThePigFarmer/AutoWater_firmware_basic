#include <DS3231.h>

Time DS3231::getTime()
{
    Time t;

    // send request to receive data starting at register 0
    Wire.beginTransmission(DS3231_ADDR);
    Wire.write((byte)0); // start at register 0
    Wire.endTransmission();

    Wire.requestFrom(DS3231_ADDR, 3); // request three bytes (ss, mi, hh)
    // check for a reply from the RTC, and use it if we can

    if (Wire.available() >= 3)
    {

        // if we're here, we got a reply and it is long enough
        // so now we read the time
        // order is important to for reading the right registers
        t.sec = bcd2bin(Wire.read());  // get seconds
        t.min = bcd2bin(Wire.read());  // get minutes
        t.hour = bcd2bin(Wire.read()); // get hours
    }

    return t;
}

// uint8_t _toBcd(uint8_t num)
// {
// 	uint8_t bcd = ((num / 10) << 4) + (num % 10);
// 	return bcd;
// }

uint8_t DS3231::bcd2bin(uint8_t num)
{
    return ((10 * ((num & 0xf0) >> 4)) + (num & 0x0f));
}