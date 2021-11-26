/*
 * modbus.h
 *
 *  Created on: Oct 31, 2021
 *      Author: kristoft
 */

#ifndef STM32_MODBUS_H_
#define STM32_MODBUS_H_

#include <stdint.h>

#define TESLA_ADDR 2

/*Function return*/
typedef enum
{
  MB_OK        = 0x00U,
  MB_ERROR     = 0x01U,
} MB_StatusTypeDef;

struct Modbus_messageRHR{
    uint8_t slaveAddr;
    uint8_t functionCode;
    uint16_t startAddr;
    uint16_t numberOfRegs;
    uint16_t msgCRC;
};

struct Modbus_messageRHRResponse{
    uint8_t slaveAddr;
    uint8_t functionCode;
    uint8_t byteCount;
    uint16_t payload[256];
    uint16_t crc;
};

void Modbus_init();
MB_StatusTypeDef Modbus_RHR(uint8_t SlaveID, uint16_t StartAddress, uint16_t NumberOfRegs, struct Modbus_messageRHRResponse *response);

#endif /* STM32_MODBUS_H_ */
