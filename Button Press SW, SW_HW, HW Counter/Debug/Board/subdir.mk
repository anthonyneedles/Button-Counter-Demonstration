################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Board/BasicIO.c \
../Board/K65TWR_GPIO.c 

OBJS += \
./Board/BasicIO.o \
./Board/K65TWR_GPIO.o 

C_DEPS += \
./Board/BasicIO.d \
./Board/K65TWR_GPIO.d 


# Each subdirectory must supply rules for building sources it contributes
Board/%.o: ../Board/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion  -g3 -I"Z:\EE344\Labs\Lab3Repo\Lab3\Board" -I"Z:\EE344\Labs\Lab3Repo\Lab3\CMSIS" -I"Z:\EE344\Labs\Lab3Repo\Lab3\Sources" -I"Z:\EE344\Labs\Lab3Repo\Lab3\Startup" -std=c99 -Wmissing-prototypes -Wstrict-prototypes -Wbad-function-cast -Wa,-adhlns="$@.lst" -ffreestanding -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


