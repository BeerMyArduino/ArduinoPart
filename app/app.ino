#include "sensors.h"
#include "constants.h"
#include "parser.h"
#include "output.h"


unsigned long start_time = -1;
int a = 0;

int output = 0;

void setup() {
	Serial.begin(9600);
	lcd.begin();
	pinMode(pin_heating, OUTPUT);
	pinMode(pin_shaker, OUTPUT);
	state = BeerState::MANUAL;
}

void loop()
{
  wrk();
}

void wrk()
{
  LOG("");
  LOG("");
	parse_BT();
  read_temp();
  control();
	output_BT();
  output_lcd();
  Serial.println(bt_str);
  delay(1000);  
}


void test_bt_lcd()
{
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,0);
  
  int i = 0;
  if (!Serial.available())
  {
    lcd.print ("Nothing");
  }
  while(Serial.available())
  {
    char c = Serial.read();
    lcd.print(c);
  }
  delay(2000);
}


void test_mode() 
{
	char s[16];
  read_temp();
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  
  
  if (temperature[LOW] < 0)
  {
    temperature[LOW] += 32;
  }
  if (temperature[HIGH] < 0)
  {
    temperature[HIGH] += 32;
  }
    
  if (temperature[TOP] > 30)
  {
    digitalWrite(pin_heating, LOW);
  }
  else
  {
    digitalWrite(pin_heating, HIGH);
  } 
  
  if (!output)
  {
    // TEMPERATURE
    lcd.setCursor(0, 0);
    lcd.print("TOP:    ");
    Serial.print("TOP = ");
    Serial.println(temperature[TOP]);
    lcd.print(temperature[TOP]);
  
  
    lcd.setCursor(0, 1);
    lcd.print("BOTTOM: ");
    Serial.print("BOTTOM = ");
    Serial.println(temperature[BOTTOM]);
    lcd.print(temperature[BOTTOM]);

	  }
	  else
	  {
      unsigned long TIME = millis();
      unsigned long SECONDS = (TIME / 1000) % 60;
      unsigned long MINUTES = (TIME / 60000) % 60;
      unsigned long HOURS = (TIME / 3600000);
      // TIME
      sprintf(s, "%02ld:%02ld:%02ld", HOURS, MINUTES, SECONDS);
      lcd.setCursor(0, 0);
      lcd.print("Time  ");
      lcd.print(s);
     
      //lcd.print(celsius);
    
      if (start_time != -1)
      {
          lcd.setCursor(0, 1);
          lcd.print("Start ");
          TIME = TIME - start_time;
          SECONDS = (TIME / 1000) % 60;
          MINUTES = (TIME / 60000) % 60;
          HOURS = (TIME / 3600000);
          sprintf(s, "%02ld:%02ld:%02ld", HOURS, MINUTES, SECONDS);
          lcd.print(s);
      }
      
      int val;
      if (Serial.available())
      {
          val = Serial.read();
          if (val == 's')
          {
              start_time = millis();
          }
          val = 0;
      }
  }

  output = output ? 0 : 1;
	delay(500);
}
	
