################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../main.cpp 

OBJS += \
./main.o 

CPP_DEPS += \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -D__CODE_RED -DCPP_USE_HEAP -D__CORTEX_M3 -DTOOLCHAIN_GCC -DMBED_BUILD_TIMESTAMP=1456861434.86 -DTOOLCHAIN_GCC_CR -DARM_MATH_CM3 -DTARGET_LIKE_CORTEX_M3 -DTARGET_CORTEX_M -DTARGET_LIKE_MBED -DTARGET_LPC176X -DTARGET_NXP -DTARGET_LPC1768 -DTARGET_M3 -DTARGET_MBED_LPC1768 -D__MBED__=1 -I"C:\EstacaoMeteo\EstacaoMet" -I"C:\EstacaoMeteo\EstacaoMet\GPS" -I"C:\EstacaoMeteo\EstacaoMet\ConfigFile" -I"C:\EstacaoMeteo\EstacaoMet\Logger" -I"C:\EstacaoMeteo\EstacaoMet\nRF24L01P" -I"C:\EstacaoMeteo\EstacaoMet\PowerControl" -I"C:\EstacaoMeteo\EstacaoMet\SHTx" -I"C:\EstacaoMeteo\EstacaoMet\mbed" -I"C:\EstacaoMeteo\EstacaoMet\mbed\TARGET_LPC1768" -I"C:\EstacaoMeteo\EstacaoMet\mbed\TARGET_LPC1768\TARGET_NXP" -I"C:\EstacaoMeteo\EstacaoMet\mbed\TARGET_LPC1768\TARGET_NXP\TARGET_LPC176X" -I"C:\EstacaoMeteo\EstacaoMet\mbed\TARGET_LPC1768\TARGET_NXP\TARGET_LPC176X\TARGET_MBED_LPC1768" -I"C:\EstacaoMeteo\EstacaoMet\mbed\TARGET_LPC1768\TOOLCHAIN_GCC_CR" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


