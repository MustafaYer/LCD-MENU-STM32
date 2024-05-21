################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/LCD/LCD_BUF.c \
../Core/LCD/i2c-lcd.c 

OBJS += \
./Core/LCD/LCD_BUF.o \
./Core/LCD/i2c-lcd.o 

C_DEPS += \
./Core/LCD/LCD_BUF.d \
./Core/LCD/i2c-lcd.d 


# Each subdirectory must supply rules for building sources it contributes
Core/LCD/%.o Core/LCD/%.su Core/LCD/%.cyclo: ../Core/LCD/%.c Core/LCD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-LCD

clean-Core-2f-LCD:
	-$(RM) ./Core/LCD/LCD_BUF.cyclo ./Core/LCD/LCD_BUF.d ./Core/LCD/LCD_BUF.o ./Core/LCD/LCD_BUF.su ./Core/LCD/i2c-lcd.cyclo ./Core/LCD/i2c-lcd.d ./Core/LCD/i2c-lcd.o ./Core/LCD/i2c-lcd.su

.PHONY: clean-Core-2f-LCD

