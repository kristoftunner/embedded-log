/*
 * modbus.h
 *
 *  Created on: Oct 31, 2021
 *      Author: kristoft
 */

#ifndef STM32_MODBUS_H_
#define STM32_MODBUS_H_

#include <stdint.h>

/*Function return*/
typedef enum
{
  MB_OK        = 0x00U,
  MB_ERROR     = 0x01U,
} MB_StatusTypeDef;

struct Modbus_messageRHR{
    uint8_t SlaveAddr;
    uint8_t FunctionCode;
    uint16_t StartAddr;
    uint16_t NumberOfRegs;
    uint16_t MsgCRC;
};

struct Modbus_messageRHRResponse{
    uint8_t SlaveAddr;
    uint8_t FunctionCode;
    uint8_t ByteCount;
    uint16_t *payload;
    uint16_t crc;
};

void Modbus_init();
MB_StatusTypeDef Modbus_RHR(uint8_t SlaveID, uint16_t StartAddress, uint16_t NumberOfRegs, struct Modbus_messageRHRResponse *response);

#endif /* STM32_MODBUS_H_ */
