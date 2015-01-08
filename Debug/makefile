################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include wan/subdir.mk
-include usart/subdir.mk
-include eeprom/subdir.mk
-include btle/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
BGAPI_Spike.lss \

FLASH_IMAGE += \
BGAPI_Spike.hex \

EEPROM_IMAGE += \
BGAPI_Spike.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: BGAPI_Spike.elf secondary-outputs

# Tool invocations
BGAPI_Spike.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,BGAPI_Spike.map -mmcu=atmega1284p -o "BGAPI_Spike.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

BGAPI_Spike.lss: BGAPI_Spike.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S BGAPI_Spike.elf  >"BGAPI_Spike.lss"
	@echo 'Finished building: $@'
	@echo ' '

BGAPI_Spike.hex: BGAPI_Spike.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex BGAPI_Spike.elf  "BGAPI_Spike.hex"
	@echo 'Finished building: $@'
	@echo ' '

BGAPI_Spike.eep: BGAPI_Spike.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex BGAPI_Spike.elf  "BGAPI_Spike.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: BGAPI_Spike.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega1284p BGAPI_Spike.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) BGAPI_Spike.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
