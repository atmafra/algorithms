################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../insertion_sort.c 

OBJS += \
./insertion_sort.o 

C_DEPS += \
./insertion_sort.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -std=c99 -I"/Users/alexandre.mafra/Documents/users/mafra/projetos/algorithms/chapter1/string_vector" -O0 -g3 -p -pg -Wall -Wconversion -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


