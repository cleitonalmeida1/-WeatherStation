################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include mbed/TARGET_LPC1768/TOOLCHAIN_GCC_CR/subdir.mk
-include Logger/subdir.mk
-include IAP/subdir.mk
-include FaultInjector/subdir.mk
-include ConfigFile/subdir.mk
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
all: ResultadoFlash.axf

# Tool invocations
ResultadoFlash.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU C++ Linker'
	arm-none-eabi-c++ -nostdlib -L"C:\-WeatherStation\ResultadoFlash" -L"C:\-WeatherStation\ResultadoFlash\ConfigFile" -L"C:\-WeatherStation\ResultadoFlash\mbed" -L"C:\-WeatherStation\ResultadoFlash\mbed\TARGET_LPC1768" -L"C:\-WeatherStation\ResultadoFlash\mbed\TARGET_LPC1768\TARGET_NXP" -L"C:\-WeatherStation\ResultadoFlash\mbed\TARGET_LPC1768\TARGET_NXP\TARGET_LPC176X" -L"C:\-WeatherStation\ResultadoFlash\mbed\TARGET_LPC1768\TARGET_NXP\TARGET_LPC176X\TARGET_MBED_LPC1768" -L"C:\-WeatherStation\ResultadoFlash\mbed\TARGET_LPC1768\TOOLCHAIN_GCC_CR" -Xlinker -Map="ResultadoFlash.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "C:\-WeatherStation\ResultadoFlash\mbed\TARGET_LPC1768\TOOLCHAIN_GCC_CR\LPC1768.ld" -o "ResultadoFlash.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) ResultadoFlash.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "ResultadoFlash.axf"; arm-none-eabi-objcopy -O binary "ResultadoFlash.axf" "ResultadoFlash.bin" ; # checksum -p LPC1768 -d "ResultadoFlash.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
