/*
 * teslactrl.c
 *
 *  Created on: 25 Nov 2021
 *      Author: usr_tunnerk
 */

#include "teslactrl.h"
#include "modbus.h"

/* Initializing all the tesla handler structs */
void tesla_init(tesla_handler *handler)
{
	tHandler = handler;

    for(int i = 0; i <sizeof(tHandler->cellVoltages)/sizeof(tHandler->cellVoltages[0]); i++)
    {
        tHandler->cellVoltages[i] = i;
        tHandler->cellVoltages[i] = i;
    }
    for(int i = 0; i < sizeof(tHandler->cellTemps)/sizeof(tHandler->cellTemps[0]); i++)
    {
        tHandler->cellTemps[i] = i;
    }
    for(int i = 0; i < sizeof(tHandler->chargerStats) / sizeof(tHandler->chargerStats); i++)
    {
        tHandler->chargerStats[i] = i;
    }
}
/* Reading out the 80 cell voltage registers */
int tesla_readCellVolts()
{
    struct Modbus_messageRHRResponse modbusMsg;
    MB_StatusTypeDef modbusStat;
    modbusStat = Modbus_RHR(TESLA_ADDR, MB_CELLVOLT_BASE, 80, &modbusMsg);
    if(modbusStat == MB_ERROR)
    {
        return 1;
    }

    for(int i = 0; i < modbusMsg.byteCount; i++)
    {
        tHandler->cellVoltages[i] = modbusMsg.payload[i];
    }

    return 0;
}

/* Reading out the 50 cell temperature registers and saving to the input structure*/
int tesla_readCellTemps()
{
    struct Modbus_messageRHRResponse modbusMsg;
    MB_StatusTypeDef modbusStat;
    modbusStat = Modbus_RHR(TESLA_ADDR, MB_CELLTEMP_BASE, 30, &modbusMsg);
    if(modbusStat == MB_ERROR)
    {
        return 1;
    }

    for(int i = 0; i < modbusMsg.byteCount/3; i++)
    {
        tHandler->cellCapacities[i*5] = modbusMsg.payload[i] >> 8;
        tHandler->cellCapacities[i*5+1] = modbusMsg.payload[i] & 0xff;
        tHandler->cellCapacities[i*5+2] = modbusMsg.payload[i+1] >> 8;
        tHandler->cellCapacities[i*5+3] = modbusMsg.payload[i+1] & 0xff;
        tHandler->cellCapacities[i*5+4] = modbusMsg.payload[i+2] >> 8;
    }

    return 0;
}

/* Reading out the 80 cell capacity registers */
int tesla_readCellCapacities()
{
    struct Modbus_messageRHRResponse modbusMsg;
    MB_StatusTypeDef modbusStat;
    modbusStat = Modbus_RHR(TESLA_ADDR, MB_CELLCAP_BASE, 80, &modbusMsg);
    if(modbusStat == MB_ERROR)
    {
        return 1;
    }

    for(int i = 0; i < modbusMsg.byteCount; i++)
    {
        tHandler->cellCapacities[i] = modbusMsg.payload[i];
    }

    return 0;
}

/* Reading out the 16 status registers */
int tesla_readChargerStatus(uint16_t *data)
{
    struct Modbus_messageRHRResponse modbusMsg;
    MB_StatusTypeDef modbusStat;
    modbusStat = Modbus_RHR(TESLA_ADDR, MB_STATREG_BASE, 16, &modbusMsg);
    if(modbusStat == MB_ERROR)
    {
        return 1;
    }

    for(int i = 0; i < modbusMsg.byteCount; i++)
    {
        data[i] = modbusMsg.payload[i];
    }

    return 0;
}

