#include "teslactrl.h"
#include "gsm.h"
#include "catchpenny_control.h"

/**
 * @brief parses the cell voltage and temperature values into json string specified in here <a href="http://mqtt.met3r.com/">link text</a> 
 *        working as a interface between teslactrl and gsm functions. Parses the information in the handler struct into the msg buffer
 *        Example for reading out cell values. Values in the array specifies the cell state values not the indecies
 *      {"id":0,"VoltageArray":[0,1,2,..79],"TemperatureArray":[0,1,..29],"CapacityArray":[0,1,2,...79]}
 *              24                2 digit          22             3 digit     19              2 digit   2
 *      
 * @param handler tesla_handler struct, which stores the information about the tesla charger
 * @param msg MQTT_controlMsg struct, we construct a json message into its buffer
 */
int catchpenny_parseCellValuesJson(tesla_handler *handler, MQTT_controlMsg *msg);

void catchpenny_parseInputMessage(MQTT_controlMsg *msg, catchpenny_controlMsg *cpMsg);
