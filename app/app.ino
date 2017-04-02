#include "LiquidCrystal_I2C.h"
#include "sensors.h"


char zhenya_pidor[17][17] = {
  "zhenya PIDOR    ",
  "henya PIDOR    z",
  "enya PIDOR    zh",
  "nya PIDOR    zhe",
  "ya PIDOR    zhen",
  "a PIDOR    zheny",
  " PIDOR    zhenya",
  "PIDOR    zhenya ",
  "IDOR    zhenya P",
  "DOR    zhenya PI",
  "OR    zhenya PID",
  "R    zhenya PIDO",
  "    zhenya PIDOR",
  "   zhenya PIDOR ",
  "  zhenya PIDOR  ",
  " zhenya PIDOR   "
};

LiquidCrystal_I2C lcd(0x3F, 16, 2);

unsigned long start_time = -1;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  lcd.begin();
  //lcd.print("zhenya PIDOR    ");
}

void loop(void) {
    read_temp();
    
    lcd.setCursor(0,0);
    lcd.print("          ");
    lcd.setCursor(0,1);
    lcd.print("          ");

    Serial.println(temperature[0]);
    Serial.println(temperature[1]);

    lcd.setCursor(0,0);
    lcd.print(temperature[0]);
    lcd.setCursor(0,1);
    lcd.print(temperature[1]);
    

    delay(8000);

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
