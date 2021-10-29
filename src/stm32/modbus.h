#include <stdint.h>

/*Function return*/
typedef enum 
{
  MB_OK        = 0x00U,
  MB_ERROR     = 0x01U,
} MB_StatusTypeDef;

struct ModBus_message_RHR{
    uint8_t SlaveAddr;
    uint8_t FunctionCode;
    uint16_t StartAddr;
    uint16_t NumberOfRegs;
    uint16_t MsgCRC;
};

struct Modbus_message_RHR_response{
    uint8_t SlaveAddr;
    uint8_t FunctionCode;
    uint8_t ByteCount;
    uint8_t *payload;
};

void Modbus_init();
MB_StatusTypeDef Modbus_RHR(uint8_t SlaveID, uint16_t StartAddress, uint16_t NumberOfRegs);
