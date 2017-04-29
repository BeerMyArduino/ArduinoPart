#include "LiquidCrystal_I2C.h"
#include "sensors.h"
#include "constants.h"


unsigned long start_time = -1;
int a = 0;

void setup() {
	Serial.begin(9600);
	lcd.begin();
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
}

void loop()
{

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
	