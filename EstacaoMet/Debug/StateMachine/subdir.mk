################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../StateMachine/StateMachine.cpp 

OBJS += \
./StateMachine/StateMachine.o 

CPP_DEPS += \
./StateMachine/StateMachine.d 


# Each subdirectory must supply rules for building sources it contributes
StateMachine/%.o: ../StateMachine/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -D__CODE_RED -DCPP_USE_HEAP -D__CORTEX_M3 -DTOOLCHAIN_GCC -DMBED_BUILD_TIMESTAMP=1456861434.86 -DTOOLCHAIN_GCC_CR -DARM_MATH_CM3 -DTARGET_LIKE_CORTEX_M3 -DTARGET_CORTEX_M -DTARGET_LIKE_MBED -DTARGET_LPC176X -DTARGET_NXP -DTARGET_LPC1768 -DTARGET_M3 -DTARGET_MBED_LPC1768 -D__MBED__=1 -I"C:\-WeatherStation\EstacaoMet" -I"C:\-WeatherStation\EstacaoMet\GPS" -I"C:\-WeatherStation\EstacaoMet\ConfigFile" -I"C:\-WeatherStation\EstacaoMet\Logger" -I"C:\-WeatherStation\EstacaoMet\nRF24L01P" -I"C:\-WeatherStation\EstacaoMet\PowerControl" -I"C:\-WeatherStation\EstacaoMet\SHTx" -I"C:\-WeatherStation\EstacaoMet\mbed" -I"C:\-WeatherStation\EstacaoMet\mbed\TARGET_LPC1768" -I"C:\-WeatherStation\EstacaoMet\mbed\TARGET_LPC1768\TARGET_NXP" -I"C:\-WeatherStation\EstacaoMet\mbed\TARGET_LPC1768\TARGET_NXP\TARGET_LPC176X" -I"C:\-WeatherStation\EstacaoMet\mbed\TARGET_LPC1768\TARGET_NXP\TARGET_LPC176X\TARGET_MBED_LPC1768" -I"C:\-WeatherStation\EstacaoMet\mbed\TARGET_LPC1768\TOOLCHAIN_GCC_CR" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


