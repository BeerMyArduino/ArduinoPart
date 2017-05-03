#pragma once
#include "constants.h"
/*
*	параметры проекта
*/


// текущие температуры
float temperature[2] = {0.0f, 0.0f};

// чтобы использовать temperature[TOP] и temperature[BOTTOM]
// нужно настроить при подключении датчиков
#define TOP 1
#define BOTTOM 0

// булевские переменные работы тэна и насоса
bool heating_el_works = false;
bool shaker_works = false;


/*
*	параметры рецепта
*/

// время варки в секундах
unsigned long required_boil_time = 0;

// необходимая температура в градусах ЦЭЛЬСИЯ
int required_boil_temperature = 0;

// текущее время
unsigned long current_time = 0;

// время начала варки
unsigned long boil_start = 0;

// время начала мешания
unsigned long shake_start = 0;

// время начала ожидания
unsigned long wait_start = 0;


// енумка, отв за текущее состояние нашей варни
// MANUAL - ручное управление
// BOIL - просто варит
// SHAKE - мешает (и варит, если надо)
// NOSHAKE - время после мешания, когда мешать нельзя

enum BeerState {MANUAL, BOIL, SHAKE, NOSHAKE} state;





// функции контроля
// ручное вкл/выкл тэна и мешалки, 
// переводит систему в состояние MANUAL 
void brute_control_heating_el(char command)
{
	if (command == '+')
	{
		state = BeerState::MANUAL;
		digitalWrite(pin_heating, HIGH);
		heating_el_works = true;
	} 
	else if (command == '-')
	{
		state = BeerState::MANUAL;
		digitalWrite(pin_heating, LOW);
		heating_el_works = false;
	}
}

void brute_control_shaker(char command)
{
	if (command == '+')
	{
		state = BeerState::MANUAL;
		digitalWrite(pin_shaker, HIGH);
		shaker_works = true;
	} 
	else if (command == '-')
	{
		state = BeerState::MANUAL;
		digitalWrite(pin_shaker, LOW);
		shaker_works = false;
	}
}

void control_heating_el(char command)
{
	if (command == '+')
	{
		digitalWrite(pin_heating, HIGH);
		heating_el_works = true;
	} 
	else if (command == '-')
	{
		digitalWrite(pin_heating, LOW);
		heating_el_works = false;
	}
}

void control_shaker(char command)
{
	if (command == '+')
	{
		digitalWrite(pin_shaker, HIGH);
		shaker_works = true;
	} 
	else if (command == '-')
	{
		digitalWrite(pin_shaker, LOW);
		shaker_works = false;
	}
}

void control_timer(char new_time)
{
	required_boil_time = ((unsigned long) new_time) * 60000;
}


void control_temperature(char new_temperature)
{
	required_boil_temperature = ((int) new_temperature);
}

void check_time()
{
	current_time = millis();
}

void start_boil()
{
  state = BeerState::BOIL;
  
}

void control()
{
	check_time();
	if (state == BeerState::MANUAL)
	{
		/* do nothing */
	}
	else if (state == BeerState::BOIL)
	{
    		if (temperature[LOW] < required_boil_temperature
    			&& !heating_el_works)
    		{
    			control_heating_el('+');
    		}
    		else if (temperature[LOW] > required_boil_temperature
    				&& heating_el_works)
    		{
    			control_heating_el('-');
    		}
    
    		if (temperature[LOW] > temperature[HIGH] + delta_temperature)
    		{
    			state = BeerState::SHAKE;
    			shake_start = current_time;
    			control_shaker('+');
    		}
    
        if (boil_start + required_boil_time > current_time)
        {
          state = BeerState::MANUAL;
          control_heating_el('-');
          control_shaker('-');
        }
   
	} 
	else if (state == BeerState::SHAKE)
	{
      		if (temperature[LOW] < required_boil_temperature
      			&& !heating_el_works)
      		{
      			control_heating_el('+');
      		}
      		else if (temperature[LOW] > required_boil_temperature
      				&& heating_el_works)
      		{
      			control_heating_el('-');
      		}
      
      		if (temperature[LOW] <= temperature[HIGH] + delta_temperature)
      		{
      			state = BeerState::BOIL;
      			control_shaker('-');
      		}
      
          if (boil_start + required_boil_time > current_time)
          {
            state = BeerState::MANUAL;
            control_heating_el('-');
            control_shaker('-');
          }
	}
}
