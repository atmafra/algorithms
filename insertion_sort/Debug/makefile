################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: insertion_sort

dependents:
	-cd /media/mafra/RAID\ 6.0TB/files/projetos/github/algorithms/string_vector/Debug && $(MAKE) all

# Tool invocations
insertion_sort: $(OBJS) $(USER_OBJS) /media/mafra/RAID\ 6.0TB/files/projetos/github/algorithms/string_vector/Debug/libstring_vector.a
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	gcc -L"/media/mafra/RAID 6.0TB/files/projetos/github/algorithms/string_vector/Debug" -o "insertion_sort" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) insertion_sort
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
/media/mafra/RAID\ 6.0TB/files/projetos/github/algorithms/string_vector/Debug/libstring_vector.a:

-include ../makefile.targets
