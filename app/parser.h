#include "constants.h"
#include "control.h"
#pragma once

void parse()
{
	while (Serial.available() > 0)
	{
		char command = Serial.read();
		switch (command)
		{
			case 'h': brute_control_heating_el(Serial.read()); break;
			case 'p': brute_control_shaker(Serial.read()); break;
			case 'c': control_timer(Serial.read()); break;
			case 't': control_temperature(Serial.read()); break;
		}
	}
}



