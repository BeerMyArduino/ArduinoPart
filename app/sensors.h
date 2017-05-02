#pragma once

#include <OneWire.h>
#include "constants.h"
#include "control.h"

OneWire  ds(ds_pin);
// on pin 10 (a 4.7K resistor is necessary)

void read_temp()
{
	char i;
	char present = 0;
	char type_s;
	char data[12];
	uint8_t addr[8];
	int current_sensor = 0;
	float celsius, fahrenheit;

	ds.reset_search();

	while (ds.search(addr)) 
	{
		if (OneWire::crc8(addr, 7) != addr[7]) 
		{
			return;
		}

		ds.reset();
		ds.select(addr);
		ds.write(0x44, 1);        // start conversion, with parasite power on at the end

		delay(1000);     
		// maybe 750ms is enough, maybe not
		// we might do a ds.depower() here, but the reset will take care of it.

		present = ds.reset();
		ds.select(addr);
		ds.write(0xBE);         // Read Scratchpad

		for ( i = 0; i < 9; i++) 
		{
			data[i] = ds.read();
		}

		int16_t raw = (data[1] << 8) | data[0];
		if (type_s) 
		{
			raw = raw << 3;
			if (data[7] == 0x10) 
			{
				raw = (raw & 0xFFF0) + 12 - data[6];
			}
		} 
		else 
		{
			byte cfg = (data[4] & 0x60);
			// at lower res, the low bits are undefined, so let's zero them
			if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
			else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
			else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
		}
		celsius = (float)raw / 16.0;
		temperature[current_sensor] = celsius;
		current_sensor++;
	}
	return;
}
