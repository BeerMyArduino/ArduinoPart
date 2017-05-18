#include "constants.h"
#include "control.h"

char bt_str[100];


// 


void output_BT()
{
  sprintf (bt_str, "%d %d %ld %d %ld %d %d",
    (int) temperature[TOP],
    (int) temperature[BOTTOM],
    boil_start == -1 ? required_boil_time : required_boil_time - (current_time - boil_start),  // время, оставшееся на варку
    required_boil_temperature,
    required_boil_time,
    heating_el_works ? 1 : 0,
    shaker_works ? 1 : 0
  );
}

int lcd_str_num = 0;



void output_lcd_temp()
{
    char s[16];
    lcd.setCursor(0, 0);
    lcd.print("TOP   BOT   REQ ");
    lcd.setCursor(0, 1);
    sprintf(s, "% 2d    %2d    %02d", (int)temperature[TOP], (int)temperature[BOTTOM], required_boil_temperature);
    lcd.print(s);
}

void output_lcd_time()
{
  char s[16];
  lcd.setCursor(0,0);
  unsigned long boil_time = 0;
  int hours = 0;
  int minutes = 0;
  int seconds = 0;
  if (boil_start != -1)
  {
    boil_time = current_time - boil_start;
    hours = (int) (boil_time / 3600);
    minutes = (int) (boil_time / 60 % 60);
    seconds = (int) (boil_time % 60);    
  }
  sprintf (s, "PASS: %02d:%02d:%02d", hours, minutes, seconds);
  lcd.print(s);
  
  lcd.setCursor(0,1);
  unsigned long left_time = required_boil_time - boil_time;
  hours = (int) (left_time / 3600);
  minutes = (int) (left_time / 60 % 60);
  seconds = (int) (left_time % 60);    
  sprintf (s, "LEFT: %02d:%02d:%02d", hours, minutes, seconds);
  lcd.print(s);
}

void output_lcd_heating_shaker()
{
  char s[16];
  lcd.setCursor(0,0);
  sprintf (s, "HEATING: %s", heating_el_works ? "YES" : "NO");
  lcd.print(s);
  lcd.setCursor(0,1);
  sprintf (s, "SHAKER: %s", shaker_works ? "YES" : "NO");
  lcd.print(s);
}



void output_lcd()
{
  lcd.clear();
  switch(lcd_str_num)
  {
      case 0: output_lcd_temp();
              if (state == BeerState::BOIL) lcd_str_num = 1;
              else lcd_str_num = 2;
              break;
      case 1: output_lcd_time(); lcd_str_num = 2; break;
      case 2: output_lcd_heating_shaker(); lcd_str_num = 0; break;
  }
}

