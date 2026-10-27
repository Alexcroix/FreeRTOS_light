################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/STM32F429I-Discovery/stm32f429i_discovery.c \
../Utilities/STM32F429I-Discovery/stm32f429i_discovery_eeprom.c \
../Utilities/STM32F429I-Discovery/stm32f429i_discovery_gyroscope.c \
../Utilities/STM32F429I-Discovery/stm32f429i_discovery_io.c \
../Utilities/STM32F429I-Discovery/stm32f429i_discovery_lcd.c \
../Utilities/STM32F429I-Discovery/stm32f429i_discovery_sdram.c \
../Utilities/STM32F429I-Discovery/stm32f429i_discovery_ts.c 

OBJS += \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery.o \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_eeprom.o \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_gyroscope.o \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_io.o \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_lcd.o \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_sdram.o \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_ts.o 

C_DEPS += \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery.d \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_eeprom.d \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_gyroscope.d \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_io.d \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_lcd.d \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_sdram.d \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_ts.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/STM32F429I-Discovery/%.o Utilities/STM32F429I-Discovery/%.su Utilities/STM32F429I-Discovery/%.cyclo: ../Utilities/STM32F429I-Discovery/%.c Utilities/STM32F429I-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F429ZITx -DSTM32F429I_DISC1 -DDEBUG -DSTM32F429xx -DUSE_HAL_DRIVER -DUSE_RTOS_SYSTICK -c -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/ili9325" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/s25fl512s" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/cs43l22" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/ili9341" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/ampire480272" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/n25q512a" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/s5k5cag" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/mfxstm32l152" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/CMSIS/device" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/n25q128a" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/ts3510" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/st7735" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/HAL_Driver/Inc/Legacy" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/lis302dl" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/otm8009a" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/stmpe1600" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/Common" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/ov2640" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/l3gd20" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/HAL_Driver/Inc" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/stmpe811" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/lis3dsh" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/wm8994" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Fonts" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/n25q256a" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/inc" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/ls016b8uy" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/ft6x06" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/exc7200" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/st7789h2" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Log" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/ampire640480" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/Components/lsm303dlhc" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/CMSIS/core" -I"C:/Users/tjoubert.LAN/STM32CubeIDE/workspace_1.3.0/F429I_LCD_ADC/Utilities/STM32F429I-Discovery" -O0 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Utilities-2f-STM32F429I-2d-Discovery

clean-Utilities-2f-STM32F429I-2d-Discovery:
	-$(RM) ./Utilities/STM32F429I-Discovery/stm32f429i_discovery.cyclo ./Utilities/STM32F429I-Discovery/stm32f429i_discovery.d ./Utilities/STM32F429I-Discovery/stm32f429i_discovery.o ./Utilities/STM32F429I-Discovery/stm32f429i_discovery.su ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_eeprom.cyclo ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_eeprom.d ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_eeprom.o ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_eeprom.su ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_gyroscope.cyclo ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_gyroscope.d ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_gyroscope.o ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_gyroscope.su ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_io.cyclo ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_io.d ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_io.o ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_io.su ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_lcd.cyclo ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_lcd.d ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_lcd.o ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_lcd.su ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_sdram.cyclo ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_sdram.d ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_sdram.o ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_sdram.su ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_ts.cyclo ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_ts.d ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_ts.o ./Utilities/STM32F429I-Discovery/stm32f429i_discovery_ts.su

.PHONY: clean-Utilities-2f-STM32F429I-2d-Discovery

