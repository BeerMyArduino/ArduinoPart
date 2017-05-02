#include "LiquidCrystal_I2C.h"
#pragma once
// nado posmotret, kakie nomera u etih pinov

// ten (heating element)
const uint8_t pin_heating = 7;

// meshalka (shaker)
const uint8_t pin_shaker = 8;

// ds temperature pin
const uint8_t ds_pin = 10;

// lcd object
LiquidCrystal_I2C lcd(0x3F, 16, 2);

/*
*  внутренние параметры системы
*/

// я думаю так: если температура различна
// в более чем delta_temperature (в цельсиях),
// то включаем насос на период времени shaker_period
// взял из головы

int delta_temperature = 10;

unsigned long shaker_period = 18000;

