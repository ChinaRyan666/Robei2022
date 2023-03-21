            ################################################################################
        # Automatically-generated file. Do not edit!
            ################################################################################

# Add inputs and outputs from these tool invocations to the build variables 


C_SRCS += \
./robei_sdk/drivers/robei_MPU.c\
./robei_sdk/drivers/robei_GPIO.c\
./robei_sdk/drivers/robei_DMA.c\
./robei_sdk/drivers/robei_IIC.c\
./robei_sdk/drivers/robei_IWDG.c\
./robei_sdk/drivers/robei_MEMIO.c\
./robei_sdk/drivers/robei_RTC.c\
./robei_sdk/drivers/robei_SPI.c\
./robei_sdk/drivers/robei_SYSCLK.c\
./robei_sdk/drivers/robei_WWDG.c\
./robei_sdk/drivers/robei_IT.c\
./robei_sdk/drivers/robei_UART.c\
./robei_sdk/drivers/robei_TIM16.c\
./robei_sdk/drivers/robei_TIM32.c

O_SRCS += \
./robei_sdk/drivers/robei_MPU.o\
./robei_sdk/drivers/robei_GPIO.o\
./robei_sdk/drivers/robei_DMA.o\
./robei_sdk/drivers/robei_IIC.o\
./robei_sdk/drivers/robei_IWDG.o\
./robei_sdk/drivers/robei_MEMIO.o\
./robei_sdk/drivers/robei_RTC.o\
./robei_sdk/drivers/robei_SPI.o\
./robei_sdk/drivers/robei_SYSCLK.o\
./robei_sdk/drivers/robei_WWDG.o\
./robei_sdk/drivers/robei_IT.o\
./robei_sdk/drivers/robei_UART.o\
./robei_sdk/drivers/robei_TIM16.o\
./robei_sdk/drivers/robei_TIM32.o

OBJS += \
./robei_sdk/drivers/robei_MPU.o\
./robei_sdk/drivers/robei_GPIO.o\
./robei_sdk/drivers/robei_DMA.o\
./robei_sdk/drivers/robei_IIC.o\
./robei_sdk/drivers/robei_IWDG.o\
./robei_sdk/drivers/robei_MEMIO.o\
./robei_sdk/drivers/robei_RTC.o\
./robei_sdk/drivers/robei_SPI.o\
./robei_sdk/drivers/robei_SYSCLK.o\
./robei_sdk/drivers/robei_WWDG.o\
./robei_sdk/drivers/robei_IT.o\
./robei_sdk/drivers/robei_UART.o\
./robei_sdk/drivers/robei_TIM16.o\
./robei_sdk/drivers/robei_TIM32.o

C_DEPS += \
./robei_sdk/drivers/robei_MPU.d\
./robei_sdk/drivers/robei_GPIO.d\
./robei_sdk/drivers/robei_DMA.d\
./robei_sdk/drivers/robei_IIC.d\
./robei_sdk/drivers/robei_IWDG.d\
./robei_sdk/drivers/robei_MEMIO.d\
./robei_sdk/drivers/robei_RTC.d\
./robei_sdk/drivers/robei_SPI.d\
./robei_sdk/drivers/robei_SYSCLK.d\
./robei_sdk/drivers/robei_WWDG.d\
./robei_sdk/drivers/robei_IT.d\
./robei_sdk/drivers/robei_UART.d\
./robei_sdk/drivers/robei_TIM16.d\
./robei_sdk/drivers/robei_TIM32.d
# Each subdirectory must supply rules for building sources it contributes
./robei_sdk/drivers/%.o: ./robei_sdk/drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv64-unknown-elf-gcc -march=rv32im -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -O0 -ffunction-sections -fdata-sections  -g3 -DDONT_USE_PLIC -DDONT_USE_M_TIME -I"C:/Users/86139/Desktop/robei/led/robei_sdk/drivers" -I"C:/Users/86139/Desktop/robei/led/inc" -I"C:/Users/86139/Desktop/robei/led/robei_sdk/env" -I"C:/Users/86139/Desktop/robei/led/robei_sdk/env/robei" -I"C:/Users/86139/Desktop/robei/led/robei_sdk/include" -Wall -ffunction-sections -fdata-sections -include sys/cdefs.h -fno-builtin-printf -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

