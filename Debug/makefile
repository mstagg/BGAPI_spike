################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include wan/subdir.mk
-include usart/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
BGAPI-Spike.lss \

FLASH_IMAGE += \
BGAPI-Spike.hex \

EEPROM_IMAGE += \
BGAPI-Spike.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: BGAPI-Spike.elf secondary-outputs

# Tool invocations
BGAPI-Spike.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,BGAPI-Spike.map -mmcu=atmega1284p -o "BGAPI-Spike.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

BGAPI-Spike.lss: BGAPI-Spike.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S BGAPI-Spike.elf  >"BGAPI-Spike.lss"
	@echo 'Finished building: $@'
	@echo ' '

BGAPI-Spike.hex: BGAPI-Spike.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex BGAPI-Spike.elf  "BGAPI-Spike.hex"
	@echo 'Finished building: $@'
	@echo ' '

BGAPI-Spike.eep: BGAPI-Spike.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex BGAPI-Spike.elf  "BGAPI-Spike.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: BGAPI-Spike.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega1284p BGAPI-Spike.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) BGAPI-Spike.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
