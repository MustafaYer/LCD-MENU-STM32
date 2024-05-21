################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/MENU/TIME/TIME.c 

OBJS += \
./Core/MENU/TIME/TIME.o 

C_DEPS += \
./Core/MENU/TIME/TIME.d 


# Each subdirectory must supply rules for building sources it contributes
Core/MENU/TIME/%.o Core/MENU/TIME/%.su Core/MENU/TIME/%.cyclo: ../Core/MENU/TIME/%.c Core/MENU/TIME/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/musta/STM32CubeIDE/workspace_1.14.1/LCD_MENU/Core/MENU/DEFAULT_SETTINGS" -I"C:/Users/musta/STM32CubeIDE/workspace_1.14.1/LCD_MENU/Core/MENU/LANGUAGE" -I"C:/Users/musta/STM32CubeIDE/workspace_1.14.1/LCD_MENU/Core/ROTARY_ENCODER" -I"C:/Users/musta/STM32CubeIDE/workspace_1.14.1/LCD_MENU/Core/RTC" -I"C:/Users/musta/STM32CubeIDE/workspace_1.14.1/LCD_MENU/Core/MENU" -I"C:/Users/musta/STM32CubeIDE/workspace_1.14.1/LCD_MENU/Core/LCD" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-MENU-2f-TIME

clean-Core-2f-MENU-2f-TIME:
	-$(RM) ./Core/MENU/TIME/TIME.cyclo ./Core/MENU/TIME/TIME.d ./Core/MENU/TIME/TIME.o ./Core/MENU/TIME/TIME.su

.PHONY: clean-Core-2f-MENU-2f-TIME

