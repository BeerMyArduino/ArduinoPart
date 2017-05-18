#include "constants.h"
#include "control.h"
#pragma once

char in_BT_str[100];
int i;

void parse_BT()
{
	for (i = 0; Serial.available() > 0 && i < 99; i++)
	{
		in_BT_str[i] = Serial.read();
	}
  in_BT_str[i] = 0;
  long parsed_time = 0;
  for (int j = 0; j < i; ++j)
  {
    switch (in_BT_str[j])
    {
      case 'h': brute_control_heating_el(in_BT_str[j+1]); j++; break;
      case 'p': brute_control_shaker(in_BT_str[j+1]); j++; break;
      
      // надо поменять
      case 'c': 
                parsed_time = 0;
                // часы
                parsed_time += ( (in_BT_str[j+1] - '0') * 10 + (in_BT_str[j+2] - '0') ) * 3600;
                // минуты
                parsed_time += ( (in_BT_str[j+4] - '0') * 10 + (in_BT_str[j+5] - '0') ) * 60;
                // секунды
                parsed_time += ( (in_BT_str[j+7] - '0') * 10 + (in_BT_str[j+8] - '0') );
                control_timer(parsed_time); 
                    j+=8; 
                    
                    break;

                    
      case 't': control_temperature( (in_BT_str[j+1] - '0') * 10 + (in_BT_str[j+2] - '0')); j+=2; break;
    }

    start_boil();
  }


//  "h-$p-$c__:__:__$t__"

  
}



