################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include mbed/TARGET_LPC1768/TOOLCHAIN_GCC_CR/subdir.mk
-include Logger/subdir.mk
-include FaultRecovery/subdir.mk
-include FaultInjector/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: ResultadoMaquinaEstadosInjectorFault.axf

# Tool invocations
ResultadoMaquinaEstadosInjectorFault.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU C++ Linker'
	arm-none-eabi-c++ -nostdlib -L"C:\-WeatherStation\ResultadoMaquinaEstadosInjectorFault" -L"C:\-WeatherStation\ResultadoMaquinaEstadosInjectorFault\ConfigFile" -L"C:\-WeatherStation\ResultadoMaquinaEstadosInjectorFault\mbed" -L"C:\-WeatherStation\ResultadoMaquinaEstadosInjectorFault\mbed\TARGET_LPC1768" -L"C:\-WeatherStation\ResultadoMaquinaEstadosInjectorFault\mbed\TARGET_LPC1768\TARGET_NXP" -L"C:\-WeatherStation\ResultadoMaquinaEstadosInjectorFault\mbed\TARGET_LPC1768\TARGET_NXP\TARGET_LPC176X" -L"C:\-WeatherStation\ResultadoMaquinaEstadosInjectorFault\mbed\TARGET_LPC1768\TARGET_NXP\TARGET_LPC176X\TARGET_MBED_LPC1768" -L"C:\-WeatherStation\ResultadoMaquinaEstadosInjectorFault\mbed\TARGET_LPC1768\TOOLCHAIN_GCC_CR" -Xlinker -Map="ResultadoMaquinaEstadosInjectorFault.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "C:\-WeatherStation\ResultadoMaquinaEstadosInjectorFault\mbed\TARGET_LPC1768\TOOLCHAIN_GCC_CR\LPC1768.ld" -o "ResultadoMaquinaEstadosInjectorFault.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) ResultadoMaquinaEstadosInjectorFault.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "ResultadoMaquinaEstadosInjectorFault.axf"; arm-none-eabi-objcopy -O binary "ResultadoMaquinaEstadosInjectorFault.axf" "ResultadoMaquinaEstadosInjectorFault.bin" ; # checksum -p LPC1768 -d "ResultadoMaquinaEstadosInjectorFault.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
