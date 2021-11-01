################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/media/kristoft/E1/Dev/projects/work/PRJ004/software/teslactrl/src/stm32/crc.c \
/media/kristoft/E1/Dev/projects/work/PRJ004/software/teslactrl/src/stm32/ili9163.c \
/media/kristoft/E1/Dev/projects/work/PRJ004/software/teslactrl/src/stm32/interface.c \
/media/kristoft/E1/Dev/projects/work/PRJ004/software/teslactrl/src/stm32/modbus.c 

OBJS += \
./Core/stm32/crc.o \
./Core/stm32/ili9163.o \
./Core/stm32/interface.o \
./Core/stm32/modbus.o 

C_DEPS += \
./Core/stm32/crc.d \
./Core/stm32/ili9163.d \
./Core/stm32/interface.d \
./Core/stm32/modbus.d 


# Each subdirectory must supply rules for building sources it contributes
Core/stm32/crc.o: /media/kristoft/E1/Dev/projects/work/PRJ004/software/teslactrl/src/stm32/crc.c Core/stm32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F765xx -c -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I"/media/kristoft/E1/Dev/projects/work/PRJ004/software/teslactrl/src/stm32" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/stm32/crc.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/stm32/ili9163.o: /media/kristoft/E1/Dev/projects/work/PRJ004/software/teslactrl/src/stm32/ili9163.c Core/stm32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F765xx -c -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I"/media/kristoft/E1/Dev/projects/work/PRJ004/software/teslactrl/src/stm32" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/stm32/ili9163.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/stm32/interface.o: /media/kristoft/E1/Dev/projects/work/PRJ004/software/teslactrl/src/stm32/interface.c Core/stm32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F765xx -c -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I"/media/kristoft/E1/Dev/projects/work/PRJ004/software/teslactrl/src/stm32" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/stm32/interface.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/stm32/modbus.o: /media/kristoft/E1/Dev/projects/work/PRJ004/software/teslactrl/src/stm32/modbus.c Core/stm32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F765xx -c -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I"/media/kristoft/E1/Dev/projects/work/PRJ004/software/teslactrl/src/stm32" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/stm32/modbus.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

