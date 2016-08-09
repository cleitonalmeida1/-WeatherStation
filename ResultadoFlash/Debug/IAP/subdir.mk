################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../IAP/IAP.cpp 

OBJS += \
./IAP/IAP.o 

CPP_DEPS += \
./IAP/IAP.d 


# Each subdirectory must supply rules for building sources it contributes
IAP/%.o: ../IAP/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -D__CODE_RED -DCPP_USE_HEAP -DTARGET_MBED_LPC1768 -DDEVICE_ERROR_PATTERN=1 -D__MBED__=1 -DDEVICE_I2CSLAVE=1 -DTARGET_LIKE_MBED -DTARGET_NXP -DTARGET_LPC176X -D__MBED_CMSIS_RTOS_CM -DDEVICE_RTC=1 -DTOOLCHAIN_object -D__CMSIS_RTOS -DTOOLCHAIN_GCC -DDEVICE_CAN=1 -DTARGET_LIKE_CORTEX_M3 -DTARGET_CORTEX_M -DARM_MATH_CM3 -DDEVICE_ANALOGOUT=1 -DTARGET_UVISOR_UNSUPPORTED -DMBED_BUILD_TIMESTAMP=1469571479.14 -DDEVICE_PWMOUT=1 -DDEVICE_INTERRUPTIN=1 -DDEVICE_I2C=1 -DDEVICE_PORTOUT=1 -D__CORTEX_M3 -DDEVICE_STDIO_MESSAGES=1 -DTARGET_M3 -DTARGET_LPC1768 -DTOOLCHAIN_GCC_CR -DDEVICE_PORTINOUT=1 -DDEVICE_SERIAL_FC=1 -DTARGET_RELEASE -DDEVICE_PORTIN=1 -DDEVICE_SLEEP=1 -DDEVICE_SPI=1 -DDEVICE_ETHERNET=1 -DDEVICE_SPISLAVE=1 -DDEVICE_ANALOGIN=1 -DDEVICE_SERIAL=1 -DDEVICE_SEMIHOST=1 -DDEVICE_DEBUG_AWARENESS=1 -DDEVICE_LOCALFILESYSTEM=1 -I"C:\-WeatherStation\ResultadoFlash" -I"C:\-WeatherStation\ResultadoFlash\ConfigFile" -I"C:\-WeatherStation\ResultadoFlash\mbed" -I"C:\-WeatherStation\ResultadoFlash\mbed\TARGET_LPC1768" -I"C:\-WeatherStation\ResultadoFlash\mbed\TARGET_LPC1768\TARGET_NXP" -I"C:\-WeatherStation\ResultadoFlash\mbed\TARGET_LPC1768\TARGET_NXP\TARGET_LPC176X" -I"C:\-WeatherStation\ResultadoFlash\mbed\TARGET_LPC1768\TARGET_NXP\TARGET_LPC176X\TARGET_MBED_LPC1768" -I"C:\-WeatherStation\ResultadoFlash\mbed\TARGET_LPC1768\TOOLCHAIN_GCC_CR" -O0 -g3 -Wall -c -std=gnu++98 -fno-rtti -Wvla -include mbed_config.h -c -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -fmessage-length=0 -fno-exceptions -fno-builtin -ffunction-sections -fdata-sections -funsigned-char -MMD -fno-delete-null-pointer-checks -fomit-frame-pointer -mcpu=cortex-m3 -mthumb -Os -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


