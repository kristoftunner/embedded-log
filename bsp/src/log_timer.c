#include "log_timer.h"

extern CRC_HandleTypeDef hcrc;

void time_init(time_logTime *thandler)
{
	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef sDate = {0};
	ltHandler = thandler;
    
    sTime.Hours = 0x18;		//represented in decimal
    sTime.Minutes = 0x30;		//represented in decimal
    sTime.Seconds = 0x0;	//represented in hexa
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;

    sDate.WeekDay = RTC_WEEKDAY_WEDNESDAY;
    sDate.Month = RTC_MONTH_JANUARY;
    sDate.Date = 0x5;		//represented in hexa
    sDate.Year = 0x22;		//represented in hexa
    //if(HAL_RTCEx_BKUPRead(ltHandler->rtc, RTC_BKP_DR0) != 0x32f2)
    //{
    	HAL_StatusTypeDef stat = HAL_OK;
    	stat = HAL_RTC_SetTime(ltHandler->rtc, &sTime, RTC_FORMAT_BCD);
    	stat = HAL_RTC_SetDate(ltHandler->rtc, &sDate, RTC_FORMAT_BCD);

    	HAL_RTCEx_BKUPWrite(ltHandler->rtc, RTC_BKP_DR0, 0x32f2);
    //}
}

void time_updateTimeStamp()
{
	RTC_DateTypeDef sDate;
	RTC_TimeTypeDef sTime;
	HAL_StatusTypeDef stat;

	stat = HAL_RTC_GetTime(ltHandler->rtc, &sTime, RTC_FORMAT_BCD);
	stat = HAL_RTC_GetDate(ltHandler->rtc, &sDate, RTC_FORMAT_BCD);

	/* format the timestamp into ltHandler properly*/
	//['INF', '2021-05-02_05:23', 'main', 'teslactrl', 'Logging started']
	//2021-05-02_05:23
	ltHandler->min = (sTime.Minutes & 0x0f) + ((sTime.Minutes & 0xf0)>>4)*10;
	ltHandler->hour = (sTime.Hours & 0x0f) + ((sTime.Hours & 0xf0)>>4)*10;
	ltHandler->day = (sDate.Date & 0x0f) + ((sDate.Date & 0xf0)>>4)*10;
	ltHandler->month = sDate.Month;
	ltHandler->year = (sDate.Year & 0x0f) + ((sDate.Year & 0xf0)>>4)*10 + 2000;

	sprintf(ltHandler->dayParsed,"%d-%d-%d_%d:%d",ltHandler->year,ltHandler->month, ltHandler->day, ltHandler->hour, ltHandler->min);
}
