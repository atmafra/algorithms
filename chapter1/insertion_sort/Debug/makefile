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
	-cd /Users/alexandre.mafra/Documents/users/mafra/projetos/algorithms/chapter1/string_vector/Debug && $(MAKE) all

# Tool invocations
insertion_sort: $(OBJS) $(USER_OBJS) /Users/alexandre.mafra/Documents/users/mafra/projetos/algorithms/chapter1/string_vector/Debug/libstring_vector.so
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	gcc -L"/Users/alexandre.mafra/Documents/users/mafra/projetos/algorithms/chapter1/string_vector/Debug" -p -pg -o "insertion_sort" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) insertion_sort
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
/Users/alexandre.mafra/Documents/users/mafra/projetos/algorithms/chapter1/string_vector/Debug/libstring_vector.so:

-include ../makefile.targets
