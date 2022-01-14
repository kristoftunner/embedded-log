#include "cmsis_os2.h"
#include <stdint.h>
#include "teslactrl.h"
#include "gsm.h"

/**
 * @brief enumeration for MQTT configure message types 
 *        Documentation of the configure message is here: <a href="http://mqtt.met3r.com/#operation-subscribe-Catchpenny/1/0/action/{E2S2_Id}/Configure">link text</a> 
 *        In the future if the configuration types are updated extend the <json_parseInputMessage>"()" function
 */
typedef enum {
    CP_MSG_CONFIG,
    CP_MSG_PWR_REQUEST,
    CP_MSG_GET_CELLS,
    CP_MSG_GET_STATUSUPDATE
}catchpenny_controlMsgType;

/**
 * @brief 
 * 
 */
typedef enum{
    MAX_CHARGE_VOLTAGE,
    MIN_CHARGE_VOLTAGE,
    MAX_CHARGE_CURRENT,
    MIN_CHARGE_CURRENT,
}catchpenny_controlMsgConfigType;

/**
 * @brief enumeration for catchpenny system overall status 
 * 
 */
typedef enum {
    CP_DISCHARGE_START,
    CP_DISCHARGE_STOP,
    CP_CHARGE_START,
    CP_CHARGE_STOP
}catchpenny_status;

/**
 * @brief struct containing the catchpenny MQTT control message attributes 
 * 
 */
typedef struct{
    catchpenny_controlMsgType type;
    catchpenny_controlMsgConfigType configType;
    int value;
}catchpenny_controlMsg;

/**
 * @brief struct containing all the variables needed to handle the communication 
 * 
 */
typedef struct{
    catchpenny_status   cpStatus;
    osMessageQueueId_t  publishQueue;
    osMessageQueueId_t  subrscribeQueue;
    osTimerId_t         statusPublishTimer;
    unsigned int        statusPulbishTimerTime;
    uint16_t            maxChargeCurrent;
    uint16_t            minChargeCurrent;
    uint16_t            maxDischargeCurrent;
    uint16_t            minDischargeCurrent;
    uint16_t            maxChargeVoltage;
    uint16_t            minChargeVoltage;
    uint16_t            maxDischargeVoltage;
    uint16_t            minDischargeVoltage; 
}catchpenny_control;

catchpenny_control *cpControl;

/**
 * @brief Initializer function for the catchpenny controller 
 * 
 * @param cp pointer to the catchpenny control block
 */

void catchpenny_Init(catchpenny_control *cp);
void catchpenny_Process();

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

/**
 * @brief function to parse the mqtt input message from the server
 * 
 * @param msg pointer to the mqtt message structure
 * @param cpMsg pointer to the catchpenny control structure into which the message is parsed
 */

void catchpenny_parseInputMessage(MQTT_controlMsg *msg, catchpenny_controlMsg *cpMsg);
