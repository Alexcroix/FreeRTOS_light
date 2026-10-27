################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/Components/ts3510/ts3510.c 

OBJS += \
./Utilities/Components/ts3510/ts3510.o 

C_DEPS += \
./Utilities/Components/ts3510/ts3510.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/Components/ts3510/%.o Utilities/Components/ts3510/%.su Utilities/Components/ts3510/%.cyclo: ../Utilities/Components/ts3510/%.c Utilities/Components/ts3510/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F429ZITx -DSTM32F429I_DISC1 -DDEBUG -DSTM32F429xx -DUSE_HAL_DRIVER -DUSE_RTOS_SYSTICK -c -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/ili9325" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/s25fl512s" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/cs43l22" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/ili9341" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/ampire480272" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/n25q512a" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/s5k5cag" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/mfxstm32l152" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/CMSIS/device" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/n25q128a" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/ts3510" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/st7735" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/HAL_Driver/Inc/Legacy" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/lis302dl" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/otm8009a" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/stmpe1600" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/Common" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/ov2640" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/l3gd20" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/HAL_Driver/Inc" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/stmpe811" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/lis3dsh" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/wm8994" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Fonts" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/n25q256a" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/inc" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/ls016b8uy" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/ft6x06" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/exc7200" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/st7789h2" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Log" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/ampire640480" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/lsm303dlhc" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/CMSIS/core" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/STM32F429I-Discovery" -O0 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Utilities-2f-Components-2f-ts3510

clean-Utilities-2f-Components-2f-ts3510:
	-$(RM) ./Utilities/Components/ts3510/ts3510.cyclo ./Utilities/Components/ts3510/ts3510.d ./Utilities/Components/ts3510/ts3510.o ./Utilities/Components/ts3510/ts3510.su

.PHONY: clean-Utilities-2f-Components-2f-ts3510

