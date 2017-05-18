#pragma once
#include "constants.h"
/*
*  параметры проекта
*/


// текущие температуры
float temperature[2] = {0.0f, 0.0f};

// чтобы использовать temperature[TOP] и temperature[BOTTOM]
#define TOP 1
#define BOTTOM 0

// булевские переменные работы тэна и насоса
bool heating_el_works = false;
bool shaker_works = false;


/*
*  параметры рецепта
*/

// время варки в секундах
unsigned long required_boil_time = 0;

// необходимая температура в градусах ЦЭЛЬСИЯ
int required_boil_temperature = 0;

// текущее время в секундах
unsigned long current_time = 0;

// время начала варки в секундах 
unsigned long boil_start = -1;

// время начала мешания в секундах
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



// не ручное изменение состояний мешалки и ТЭНа. не переключаемся в MANUAL
void control_heating_el(char command)
{
  if (command == '+')
  {
    LOG("    control heating '+'   --  should start heat");
    digitalWrite(pin_heating, HIGH);
    heating_el_works = true;
  } 
  else if (command == '-')
  {
    LOG("    control heating '-'   --  should stop heat");
    digitalWrite(pin_heating, LOW);
    heating_el_works = false;
  }
}

void control_shaker(char command)
{
  if (command == '+')
  {
    LOG("    control shaker '+'   --  should start shake");
    digitalWrite(pin_shaker, HIGH);
    shaker_works = true;
  } 
  else if (command == '-')
  {
    LOG("    control shaker '-'   --  should stop shake");
    digitalWrite(pin_shaker, LOW);
    shaker_works = false;
  }
}

void control_timer(long new_time_seconds)
{
  required_boil_time = ((unsigned long) new_time_seconds);
}


void control_temperature(char new_temperature)
{
  required_boil_temperature = ((int) new_temperature);
}

void check_time()
{
  current_time = millis() / 1000;
}

void start_boil()
{
  state = BeerState::BOIL;
  
}



// MAIN CONTROL FUNCTION
void control()
{
  LOG("control function");
  check_time();
  if (state == BeerState::MANUAL)
  {
    LOG("  manual state -> do nothing");
    if (boil_start != -1)
    {
      boil_start = -1;
    }

    if (required_boil_temperature != 0)
    {
      required_boil_temperature = 0;
    }

    if (required_boil_time != 0)
    {
      required_boil_time = 0;
    }
  }
  else if (state == BeerState::BOIL)
  {
        LOG("  boil state");
        if (temperature[LOW] < required_boil_temperature  &&  !heating_el_works)
        {
          LOG("  low temp < required and heat no works -> should start heat");
          control_heating_el('+');
        }
        else if (temperature[LOW] > required_boil_temperature  &&  heating_el_works)
        {
          LOG("  too high temp ->  should stop heat");
          control_heating_el('-');
          if (boil_start == -1)
          {
            LOG("  boil first time and should record start_boil_time");
            boil_start = current_time;
            LOG("  boil_start", boil_start);
          }
          
        }
        int current_delta_temperature = temperature[LOW] - temperature[HIGH];
        current_delta_temperature = current_delta_temperature > 0 ? current_delta_temperature : -current_delta_temperature;
        if (current_delta_temperature > delta_temperature)
        {
          LOG("  current_delta_temp > delta -> start shake it baby");
          state = BeerState::SHAKE;
          shake_start = current_time;
          control_shaker('+');
        }
    
        if (
          
              (boil_start != -1)  &&  (boil_start + required_boil_time < current_time) 
            )
        {

          LOG("  time is up, so take manual state again");
          state = BeerState::MANUAL;
          control_heating_el('-');
          control_shaker('-');
        }
   
  } 
  else if (state == BeerState::SHAKE)
  {
    LOG("  SHAKE state");
    
    if ( (
            temperature[LOW] < required_boil_temperature 
            || temperature[HIGH] < required_boil_temperature
          )
          && !heating_el_works
       )
    {
      LOG("  low temp < required and heat no works -> should start heat");
      control_heating_el('+');
    }
    else if (
             temperature[LOW] > required_boil_temperature 
             || temperature[HIGH] > required_boil_temperature
            )
    {
      LOG("  too high temp ->  should stop heat");
      if(heating_el_works) control_heating_el('-');
      if (boil_start == -1)
      {
        LOG("  boil first time and should record start_boil_time");
        boil_start = current_time;
        LOG("  boil_start", boil_start);
      }
    }
    int current_delta_temperature = temperature[LOW] - temperature[HIGH];
    current_delta_temperature = current_delta_temperature > 0 ? current_delta_temperature : -current_delta_temperature;
    if (current_delta_temperature <= delta_temperature / 2)
    {
      LOG("  current_delta_temp <= delta/2 -> STOP shake it baby");
      state = BeerState::BOIL;
      control_shaker('-');
    }

    if (
          (boil_start != -1) 
          && (boil_start + required_boil_time < current_time) 
       )
    {
      LOG("  time is up, so take manual state again");
      state = BeerState::MANUAL;
      control_heating_el('-');
      control_shaker('-');
    }
  }
}
