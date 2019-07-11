################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/Src/cortexm/_initialize_hardware.c \
../system/Src/cortexm/_reset_hardware.c \
../system/Src/cortexm/exception_handlers.c 

OBJS += \
./system/Src/cortexm/_initialize_hardware.o \
./system/Src/cortexm/_reset_hardware.o \
./system/Src/cortexm/exception_handlers.o 

C_DEPS += \
./system/Src/cortexm/_initialize_hardware.d \
./system/Src/cortexm/_reset_hardware.d \
./system/Src/cortexm/exception_handlers.d 


# Each subdirectory must supply rules for building sources it contributes
system/Src/cortexm/%.o: ../system/Src/cortexm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -DDEBUG -DUSE_FULL_ASSERT -DSTM32F469xx -DHSE_VALUE=8000000 -I"../Inc" -I"../system/Inc" -I"../system/Inc/cmsis" -I"../system/Inc/stm32f4-hal" -std=gnu11 -Wmissing-prototypes -Wstrict-prototypes -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


