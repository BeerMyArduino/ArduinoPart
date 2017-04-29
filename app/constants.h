
// nado posmotret, kakie nomera u etih pinov

// ten (heating element)
const uint8_t pin_heating = 7;

// meshalka (shaker)
const uint8_t pin_shaker = 8;

// ds temperature pin
const uint8_t ds_pin = 10;

// running string
char anton_pidor[17][17] = {
  "anton PIDOR     ",
  "nton PIDOR     a",
  "ton PIDOR     an",
  "on PIDOR     ant",
  "n PIDOR     anto",
  " PIDOR     anton",
  "PIDOR     anton ",
  "IDOR     anton P",
  "DOR     anton PI",
  "OR     anton PID",
  "R     anton PIDO",
  "     anton PIDOR",
  "    anton PIDOR ",
  "   anton PIDOR  ",
  "  anton PIDOR   ",
  " anton PIDOR    "
};

LiquidCrystal_I2C lcd(0x3F, 16, 2);