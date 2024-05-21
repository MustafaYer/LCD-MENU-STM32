################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/MENU/BRIGTHNESS/BRIGHTNESS.c 

OBJS += \
./Core/MENU/BRIGTHNESS/BRIGHTNESS.o 

C_DEPS += \
./Core/MENU/BRIGTHNESS/BRIGHTNESS.d 


# Each subdirectory must supply rules for building sources it contributes
Core/MENU/BRIGTHNESS/%.o Core/MENU/BRIGTHNESS/%.su Core/MENU/BRIGTHNESS/%.cyclo: ../Core/MENU/BRIGTHNESS/%.c Core/MENU/BRIGTHNESS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/musta/STM32CubeIDE/workspace_1.14.1/LCD_MENU/Core/MENU/BRIGTHNESS" -I"C:/Users/musta/STM32CubeIDE/workspace_1.14.1/LCD_MENU/Core/ROTARY_ENCODER" -I"C:/Users/musta/STM32CubeIDE/workspace_1.14.1/LCD_MENU/Core/RTC" -I"C:/Users/musta/STM32CubeIDE/workspace_1.14.1/LCD_MENU/Core/MENU" -I"C:/Users/musta/STM32CubeIDE/workspace_1.14.1/LCD_MENU/Core/LCD" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-MENU-2f-BRIGTHNESS

clean-Core-2f-MENU-2f-BRIGTHNESS:
	-$(RM) ./Core/MENU/BRIGTHNESS/BRIGHTNESS.cyclo ./Core/MENU/BRIGTHNESS/BRIGHTNESS.d ./Core/MENU/BRIGTHNESS/BRIGHTNESS.o ./Core/MENU/BRIGTHNESS/BRIGHTNESS.su

.PHONY: clean-Core-2f-MENU-2f-BRIGTHNESS

