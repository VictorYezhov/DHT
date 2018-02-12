################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/dhtxx.c \
../Src/gpio.c \
../Src/stm32f3xx_hal_msp.c \
../Src/stm32f3xx_it.c \
../Src/system_stm32f3xx.c \
../Src/tim.c \
../Src/us_timing.c 

CPP_SRCS += \
../Src/dht.cpp \
../Src/main.cpp \
../Src/pinController.cpp 

OBJS += \
./Src/dht.o \
./Src/dhtxx.o \
./Src/gpio.o \
./Src/main.o \
./Src/pinController.o \
./Src/stm32f3xx_hal_msp.o \
./Src/stm32f3xx_it.o \
./Src/system_stm32f3xx.o \
./Src/tim.o \
./Src/us_timing.o 

C_DEPS += \
./Src/dhtxx.d \
./Src/gpio.d \
./Src/stm32f3xx_hal_msp.d \
./Src/stm32f3xx_it.d \
./Src/system_stm32f3xx.d \
./Src/tim.d \
./Src/us_timing.d 

CPP_DEPS += \
./Src/dht.d \
./Src/main.d \
./Src/pinController.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F303xC -I"D:/UCU/Arcitechture 2.0/Lab1ConvertaionToC++/weather/Inc" -I"D:/UCU/Arcitechture 2.0/Lab1ConvertaionToC++/weather/Drivers/STM32F3xx_HAL_Driver/Inc" -I"D:/UCU/Arcitechture 2.0/Lab1ConvertaionToC++/weather/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"D:/UCU/Arcitechture 2.0/Lab1ConvertaionToC++/weather/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"D:/UCU/Arcitechture 2.0/Lab1ConvertaionToC++/weather/Drivers/CMSIS/Include"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F303xC -I"D:/UCU/Arcitechture 2.0/Lab1ConvertaionToC++/weather/Inc" -I"D:/UCU/Arcitechture 2.0/Lab1ConvertaionToC++/weather/Drivers/STM32F3xx_HAL_Driver/Inc" -I"D:/UCU/Arcitechture 2.0/Lab1ConvertaionToC++/weather/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"D:/UCU/Arcitechture 2.0/Lab1ConvertaionToC++/weather/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"D:/UCU/Arcitechture 2.0/Lab1ConvertaionToC++/weather/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


