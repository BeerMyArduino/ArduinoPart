#include "sensors.h"
#include "constants.h"
#include "parser.h"


unsigned long start_time = -1;
int a = 0;

void setup() {
	Serial.begin(9600);
	lcd.begin();
	pinMode(pin_heating, OUTPUT);
	pinMode(pin_shaker, OUTPUT);
	state = BeerState::MANUAL;
}

void loop()
{
	parse();
}


void ff() {
	char s[16];
	sprintf(s, "%ld", millis() / 1000);
	lcd.setCursor(0, 0);
	lcd.print(s);

	lcd.setCursor(8, 1);
	//lcd.print(celsius);

	if (start_time != -1)
	{
		lcd.setCursor(0, 1);

		sprintf(s, "%ld", (millis() - start_time) / 1000);
		lcd.print(s);
	}

	int val;
	if (Serial.available())
	{
		val = Serial.read();
		// При символе "1" включаем светодиод
		if (val == 's')
		{
			start_time = millis();
		}
		// При символе "0" выключаем светодиод
		if ( val == '0')
		{
			digitalWrite(13, LOW);
		}
		val = 0;
	}

	delay(5000);
}
	