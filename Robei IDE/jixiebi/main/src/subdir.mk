            ################################################################################
        # Automatically-generated file. Do not edit!
            ################################################################################

# Add inputs and outputs from these tool invocations to the build variables 


C_SRCS += \
./src/main.c

OBJS += \
./src/main.o

C_DEPS += \
./src/main.d
# Each subdirectory must supply rules for building sources it contributes
./src/%.o: ./src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv64-unknown-elf-gcc -march=rv32im -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -O0 -ffunction-sections -fdata-sections  -g3 -DDONT_USE_PLIC -DDONT_USE_M_TIME -I"D:/jixiebi/main/robei_sdk/drivers" -I"D:/jixiebi/main/inc" -I"D:/jixiebi/main/robei_sdk/env" -I"D:/jixiebi/main/robei_sdk/env/robei" -I"D:/jixiebi/main/robei_sdk/include" -Wall -ffunction-sections -fdata-sections -include sys/cdefs.h -fno-builtin-printf -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

