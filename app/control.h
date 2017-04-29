
/*
*	параметры проекта
*/


// температуры
float[2] temperature = {0.0f, 0.0f};

// чтобы использовать temperature[TOP] и temperature[BOTTOM]
// нужно настроить при подключении датчиков
#define TOP 1
#define BOTTOM 0

// булевские переменные работы тэна и насоса
bool heatingElWorks = false;
bool shakerWorks = false;


/*
*	параметры рецепта
*/

// время варки в секундах
unsigned long requiredBoilTime = -1;

// необходимая температура в градусах ЦЭЛЬСИЯ
int requiredBoilTime = -1;

/*
*	внутренние параметры системы
*/

// я думаю так: если температура различна
// в более чем delta_temperature (в цельсиях),
// то включаем насос на период времени shaker_period
// взял из головы

int delta_temperature = 10;

int shaker_period = 3;

