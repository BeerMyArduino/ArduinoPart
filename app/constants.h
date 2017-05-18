#include "LiquidCrystal_I2C.h"
#pragma once
// nado posmotret, kakie nomera u etih pinov

// ten (heating element)
const uint8_t pin_heating = 6;

// meshalka (shaker)
const uint8_t pin_shaker = 7;

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



// LOGGING
// В РЕЛИЗЕ ЗАКОММЕНТИРУЙТЕ ВНУТРЕННОСТИ ФУНКЦИЙ
// В ДЕБАГЕ НАСЛАЖДАЙТЕСЬ КУЧЕЙ ФЛУДА В СЕРИАЛ ПОРТЕ

void LOG(const char* s)
{
//	Serial.print("DEBUG: ");
//	Serial.println(s);
}

void LOG(const char *s1, const char *s2)
{
//	Serial.print("DEBUG: ");
//	Serial.print(s1);
//	Serial.println(s2);
}

void LOG(const char *param, unsigned long val)
{
//  Serial.print("DEBUG: ");
//  Serial.print(param);
//  Serial.print(" = ");
//  Serial.println(val);
}

