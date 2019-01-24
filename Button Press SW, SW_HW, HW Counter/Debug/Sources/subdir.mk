################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Lab3.c 

OBJS += \
./Sources/Lab3.o 

C_DEPS += \
./Sources/Lab3.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion  -g3 -I"Z:\EE344\Labs\Lab3Repo\Lab3\Board" -I"Z:\EE344\Labs\Lab3Repo\Lab3\CMSIS" -I"Z:\EE344\Labs\Lab3Repo\Lab3\Sources" -I"Z:\EE344\Labs\Lab3Repo\Lab3\Startup" -std=c99 -Wmissing-prototypes -Wstrict-prototypes -Wbad-function-cast -Wa,-adhlns="$@.lst" -ffreestanding -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


