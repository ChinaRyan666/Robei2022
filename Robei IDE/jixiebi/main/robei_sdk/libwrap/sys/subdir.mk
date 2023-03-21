            ################################################################################
        # Automatically-generated file. Do not edit!
            ################################################################################

# Add inputs and outputs from these tool invocations to the build variables 


C_SRCS += \
./robei_sdk/libwrap/sys/_exit.c\
./robei_sdk/libwrap/sys/close.c\
./robei_sdk/libwrap/sys/execve.c\
./robei_sdk/libwrap/sys/fork.c\
./robei_sdk/libwrap/sys/fstat.c\
./robei_sdk/libwrap/sys/getpid.c\
./robei_sdk/libwrap/sys/isatty.c\
./robei_sdk/libwrap/sys/kill.c\
./robei_sdk/libwrap/sys/link.c\
./robei_sdk/libwrap/sys/lseek.c\
./robei_sdk/libwrap/sys/open.c\
./robei_sdk/libwrap/sys/openat.c\
./robei_sdk/libwrap/sys/puts.c\
./robei_sdk/libwrap/sys/read.c\
./robei_sdk/libwrap/sys/sbrk.c\
./robei_sdk/libwrap/sys/stat.c\
./robei_sdk/libwrap/sys/times.c\
./robei_sdk/libwrap/sys/unlink.c\
./robei_sdk/libwrap/sys/wait.c\
./robei_sdk/libwrap/sys/write.c

O_SRCS += \
./robei_sdk/libwrap/sys/_exit.o\
./robei_sdk/libwrap/sys/close.o\
./robei_sdk/libwrap/sys/execve.o\
./robei_sdk/libwrap/sys/fork.o\
./robei_sdk/libwrap/sys/fstat.o\
./robei_sdk/libwrap/sys/getpid.o\
./robei_sdk/libwrap/sys/isatty.o\
./robei_sdk/libwrap/sys/kill.o\
./robei_sdk/libwrap/sys/link.o\
./robei_sdk/libwrap/sys/lseek.o\
./robei_sdk/libwrap/sys/open.o\
./robei_sdk/libwrap/sys/openat.o\
./robei_sdk/libwrap/sys/puts.o\
./robei_sdk/libwrap/sys/read.o\
./robei_sdk/libwrap/sys/sbrk.o\
./robei_sdk/libwrap/sys/stat.o\
./robei_sdk/libwrap/sys/times.o\
./robei_sdk/libwrap/sys/unlink.o\
./robei_sdk/libwrap/sys/wait.o\
./robei_sdk/libwrap/sys/write.o

OBJS += \
./robei_sdk/libwrap/sys/_exit.o\
./robei_sdk/libwrap/sys/close.o\
./robei_sdk/libwrap/sys/execve.o\
./robei_sdk/libwrap/sys/fork.o\
./robei_sdk/libwrap/sys/fstat.o\
./robei_sdk/libwrap/sys/getpid.o\
./robei_sdk/libwrap/sys/isatty.o\
./robei_sdk/libwrap/sys/kill.o\
./robei_sdk/libwrap/sys/link.o\
./robei_sdk/libwrap/sys/lseek.o\
./robei_sdk/libwrap/sys/open.o\
./robei_sdk/libwrap/sys/openat.o\
./robei_sdk/libwrap/sys/puts.o\
./robei_sdk/libwrap/sys/read.o\
./robei_sdk/libwrap/sys/sbrk.o\
./robei_sdk/libwrap/sys/stat.o\
./robei_sdk/libwrap/sys/times.o\
./robei_sdk/libwrap/sys/unlink.o\
./robei_sdk/libwrap/sys/wait.o\
./robei_sdk/libwrap/sys/write.o

C_DEPS += \
./robei_sdk/libwrap/sys/_exit.d\
./robei_sdk/libwrap/sys/close.d\
./robei_sdk/libwrap/sys/execve.d\
./robei_sdk/libwrap/sys/fork.d\
./robei_sdk/libwrap/sys/fstat.d\
./robei_sdk/libwrap/sys/getpid.d\
./robei_sdk/libwrap/sys/isatty.d\
./robei_sdk/libwrap/sys/kill.d\
./robei_sdk/libwrap/sys/link.d\
./robei_sdk/libwrap/sys/lseek.d\
./robei_sdk/libwrap/sys/open.d\
./robei_sdk/libwrap/sys/openat.d\
./robei_sdk/libwrap/sys/puts.d\
./robei_sdk/libwrap/sys/read.d\
./robei_sdk/libwrap/sys/sbrk.d\
./robei_sdk/libwrap/sys/stat.d\
./robei_sdk/libwrap/sys/times.d\
./robei_sdk/libwrap/sys/unlink.d\
./robei_sdk/libwrap/sys/wait.d\
./robei_sdk/libwrap/sys/write.d
# Each subdirectory must supply rules for building sources it contributes
./robei_sdk/libwrap/sys/%.o: ./robei_sdk/libwrap/sys/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv64-unknown-elf-gcc -march=rv32im -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -O0 -ffunction-sections -fdata-sections  -g3 -DDONT_USE_PLIC -DDONT_USE_M_TIME -I"D:/jixiebi/main/robei_sdk/drivers" -I"D:/jixiebi/main/inc" -I"D:/jixiebi/main/robei_sdk/env" -I"D:/jixiebi/main/robei_sdk/env/robei" -I"D:/jixiebi/main/robei_sdk/include" -Wall -ffunction-sections -fdata-sections -include sys/cdefs.h -fno-builtin-printf -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

