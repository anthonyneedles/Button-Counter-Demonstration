################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Startup/system_MK65F18.c 

S_UPPER_SRCS += \
../Startup/startup_MK65F18.S 

OBJS += \
./Startup/startup_MK65F18.o \
./Startup/system_MK65F18.o 

C_DEPS += \
./Startup/system_MK65F18.d 

S_UPPER_DEPS += \
./Startup/startup_MK65F18.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion  -g3 -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Startup/%.o: ../Startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion  -g3 -I"Z:\EE344\Labs\Lab3Repo\Lab3\Board" -I"Z:\EE344\Labs\Lab3Repo\Lab3\CMSIS" -I"Z:\EE344\Labs\Lab3Repo\Lab3\Sources" -I"Z:\EE344\Labs\Lab3Repo\Lab3\Startup" -std=c99 -Wmissing-prototypes -Wstrict-prototypes -Wbad-function-cast -Wa,-adhlns="$@.lst" -ffreestanding -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


