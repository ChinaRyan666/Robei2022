            ################################################################################
        # Automatically-generated file. Do not edit!
            ################################################################################

# Add inputs and outputs from these tool invocations to the build variables 




S_UPPER_SRCS += \
./robei_sdk/env/entry.S\
./robei_sdk/env/rtos_start.S\
./robei_sdk/env/start.S

O_SRCS += \
./robei_sdk/env/entry.o\
./robei_sdk/env/rtos_start.o\
./robei_sdk/env/start.o

OBJS += \
./robei_sdk/env/entry.o\
./robei_sdk/env/rtos_start.o\
./robei_sdk/env/start.o

S_UPPER_DEPS += \
./robei_sdk/env/entry.d\
./robei_sdk/env/rtos_start.d\
./robei_sdk/env/start.d
# Each subdirectory must supply rules for building sources it contributes
./robei_sdk/env/%.o: ./robei_sdk/env/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross Assembler'
	riscv64-unknown-elf-gcc -march=rv32im -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -O0 -ffunction-sections -fdata-sections  -g3 -x assembler-with-cpp -DportasmHANDLE_INTERRUPT=handle_trap -I"D:/jixiebi/main/robei_sdk/env" -I"D:/jixiebi/main/robei_sdk/include" -I"D:/jixiebi/main/robei_sdk/env/robei" -I"D:/jixiebi/main/robei_sdk/drivers" -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

