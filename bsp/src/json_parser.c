#include "json_parser.h"
#include "mjson.h"
#include <string.h>

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

void json_parseInputMessage(MQTT_controlMsg *msg)
{
    /* parse the input message -> input to the state machine -> do something*/
    /* egy configure-t ki kell majd próbálni */
}
