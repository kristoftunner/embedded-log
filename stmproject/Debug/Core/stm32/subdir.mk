################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/Dev/projects/work/PRJ004/software/teslactrl/src/stm32/crc.c \
E:/Dev/projects/work/PRJ004/software/teslactrl/src/stm32/fonts.c \
E:/Dev/projects/work/PRJ004/software/teslactrl/src/stm32/ili9163.c \
E:/Dev/projects/work/PRJ004/software/teslactrl/src/stm32/interface.c \
E:/Dev/projects/work/PRJ004/software/teslactrl/src/stm32/modbus.c 

OBJS += \
./Core/stm32/crc.o \
./Core/stm32/fonts.o \
./Core/stm32/ili9163.o \
./Core/stm32/interface.o \
./Core/stm32/modbus.o 

C_DEPS += \
./Core/stm32/crc.d \
./Core/stm32/fonts.d \
./Core/stm32/ili9163.d \
./Core/stm32/interface.d \
./Core/stm32/modbus.d 


# Each subdirectory must supply rules for building sources it contributes
Core/stm32/crc.o: E:/Dev/projects/work/PRJ004/software/teslactrl/src/stm32/crc.c Core/stm32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -DSTM32F765xx -c -I"E:/Dev/projects/work/PRJ004/software/teslactrl/inc" -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/stm32/crc.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/stm32/fonts.o: E:/Dev/projects/work/PRJ004/software/teslactrl/src/stm32/fonts.c Core/stm32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -DSTM32F765xx -c -I"E:/Dev/projects/work/PRJ004/software/teslactrl/inc" -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/stm32/fonts.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/stm32/ili9163.o: E:/Dev/projects/work/PRJ004/software/teslactrl/src/stm32/ili9163.c Core/stm32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -DSTM32F765xx -c -I"E:/Dev/projects/work/PRJ004/software/teslactrl/inc" -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/stm32/ili9163.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/stm32/interface.o: E:/Dev/projects/work/PRJ004/software/teslactrl/src/stm32/interface.c Core/stm32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -DSTM32F765xx -c -I"E:/Dev/projects/work/PRJ004/software/teslactrl/inc" -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/stm32/interface.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/stm32/modbus.o: E:/Dev/projects/work/PRJ004/software/teslactrl/src/stm32/modbus.c Core/stm32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -DSTM32F765xx -c -I"E:/Dev/projects/work/PRJ004/software/teslactrl/inc" -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/stm32/modbus.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

