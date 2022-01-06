#include <stdint.h>
#include "main.h"

typedef struct{
	RTC_HandleTypeDef *rtc;
	uint8_t min;
	uint8_t hour;
	uint8_t day;
	uint8_t month;
	uint16_t year;
	uint8_t dayParsed[17];
}time_logTime;

time_logTime *ltHandler;

void time_updateTimeStamp();
void time_init(time_logTime *lt);
