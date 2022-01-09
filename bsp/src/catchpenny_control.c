#include "catchpenny_control.h"
#include "log.h"
#include "log_timer.h"
#include <string.h>

static const char moduleName[] = "catchpenny_control";
void catchpenny_Init(catchpenny_control *cp)
{
    osStatus_t status;
    cpControl = cp;
    cpControl->statusPulbishTimerTime = 1000U;
    status = osTimerStart(cpControl->statusPublishTimer, cpControl->statusPulbishTimerTime);
}

void catchpenny_Process()
{
   /** 1. read and parse the MQTT message from queue
   *   2. state machine according to MQTT message
   */
  osStatus_t status;
  MQTT_controlMsg mqttMsg;
  catchpenny_controlMsg cpMsg;
  if(osTimerIsRunning(cpControl->statusPublishTimer) == 0)
  {
    /* read out charger information via RS485->parse->put into the queue->start the timer*/
    ;
    if(json_parseCellValuesJson(tHandler,&mqttMsg) != 0)
    {
         LOG_ERR("%s %s parsed json data dont fit into buffer!",moduleName, ltHandler->dayParsed);
    }

    status = osMessageQueuePut(cpControl->publishQueue, &mqttMsg, 0U , 0U);

    osStatus_t status = osTimerStart(cpControl->statusPublishTimer, cpControl->statusPulbishTimerTime);
   }

   status = osMessageQueueGet(cpControl->subrscribeQueue, &mqttMsg, 0U, 0U);
   if(status == osOK)
   {
        json_parseInputMessage(&mqttMsg, &cpMsg);
        switch(cpMsg.type){
            /* TODO: implementation */
            default:
                break;
        }
   }
}

int json_parseCellValuesJson(tesla_handler *handler, MQTT_controlMsg *msg)
{
   int size = sizeof(msg->jsonString)-1;
   int currentSize = 0;
   strcpy(msg->jsonString,"{\"id\":0,\"VoltageArray\":");
   strcat(msg->jsonString, "[");
   currentSize = strlen(msg->jsonString);
   /* copy cell voltages into json string (msjon doesnt have a functionality for array,lol)*/
   for(int i = 0; i < sizeof(handler->cellVoltages)/sizeof(handler->cellVoltages[0]); i++)
   {
       int error = 0;
	   uint8_t temp[10];
       error = sprintf(&temp[0],"%d", handler->cellVoltages[i]);
       currentSize += strlen(temp);
       strcat(msg->jsonString, temp);
       if(i != (sizeof(handler->cellVoltages)/sizeof(handler->cellVoltages[0])))
       {
           currentSize += strlen(",");
           strcat(msg->jsonString,",");
       }
   }
   currentSize += strlen("]");
   strcat(msg->jsonString, "]"); 
   currentSize += strlen(",\"TemperatureArray\":[");
   strcat(msg->jsonString,",\"TemperatureArray\":[");
   for(int i = 0; i < sizeof(handler->cellTemps)/sizeof(handler->cellTemps[0]); i++)
   {
       int error = 0;
	   uint8_t temp[10];
       error = sprintf(&temp[0],"%d", handler->cellTemps[i]);
       currentSize += strlen(temp);
       strcat(msg->jsonString, temp);
       if(i != (sizeof(handler->cellTemps)/sizeof(handler->cellTemps[0])))
       {
           currentSize += strlen(",");
           strcat(msg->jsonString,",");
       }
   }
   currentSize += strlen("]");
   strcat(msg->jsonString, "]"); 
   currentSize += strlen(",\"CapacityArray\":[");
   strcat(msg->jsonString,",\"CapacityArray\":[");
   for(int i = 0; i < sizeof(handler->cellCapacities)/sizeof(handler->cellCapacities[0]); i++)
   {
       int error = 0;
	   uint8_t temp[10];
       error = sprintf(&temp[0],"%d", handler->cellCapacities[i]);
       currentSize += strlen(temp);
       strcat(msg->jsonString, temp);
       if(i != (sizeof(handler->cellCapacities)/sizeof(handler->cellCapacities[0])))
       {
           currentSize += strlen(",");
           strcat(msg->jsonString,",");
       }
   }
   currentSize += strlen("]}");
   strcat(msg->jsonString, "]"); 
   strcat(msg->jsonString,"}");

   if(currentSize > size)
	   return -1;
   else
	   return 0;
}

void json_parseInputMessage(MQTT_controlMsg *msg, catchpenny_controlMsg *cpMsg)
{
    /* parse the input message into a catchpenny control block */
    char buff[20];
    int len = 0;
    if(mjson_get_string(msg->jsonString, strlen(msg->jsonString),"$.config",buff, sizeof(buff)) != -1)
    {
        double value; //need an array because mjson_get_number copies 64bit of value (lol)
        if(mjson_get_number(msg->jsonString, strlen(msg->jsonString), "$.value", &value))
        {
            if(strcmp(buff,"MaxChargeVoltage") == 0)
            {
                cpMsg->type = MAX_CHARGE_VOLTAGE;
                cpMsg->value = (int)value;
            }
            else if(strcmp(buff,"MinChargeVoltage") == 0)
            {
                cpMsg->type = MIN_CHARGE_VOLTAGE;
                cpMsg->value = (int)value;
            }
            else if(strcmp(buff,"MaxChargeCurrent") == 0)
            {
                cpMsg->type = MAX_CHARGE_CURRENT;
                cpMsg->value = (int)value;
            }
            else if(strcmp(buff,"MinChargeCurrent") == 0)
            {
                cpMsg->type = MIN_CHARGE_CURRENT;
                cpMsg->value = (int)value;
            }
            else if(strcmp(buff,"MaxChargeCurrent") == 0)
            {
                cpMsg->type = MAX_CHARGE_CURRENT;
                cpMsg->value = (int)value;
            }
        }
    }
    else if(mjson_get_string(msg->jsonString, strlen(msg->jsonString),"$.state",buff, sizeof(buff)) != -1)
    {
        /* TODO: implementation needed*/
        ;
    }
}

