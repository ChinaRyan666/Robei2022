            ################################################################################
        # Automatically-generated file. Do not edit!
            ################################################################################


RM := rm -rf

# All of the sources participating in the build are defined here
-include ./sources.mk
-include ./objects.mk
-include ./src/subdir.mk
-include ./inc/subdir.mk
-include ./robei_sdk/subdir.mk
-include ./robei_sdk/env/subdir.mk
-include ./robei_sdk/env/robei/subdir.mk
-include ./robei_sdk/drivers/subdir.mk
-include ./robei_sdk/libwrap/subdir.mk
-include ./robei_sdk/libwrap/misc/subdir.mk
-include ./robei_sdk/libwrap/stdlib/subdir.mk
-include ./robei_sdk/libwrap/sys/subdir.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif            
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)            
-include $(C_DEPS)
endif
endif
# Add inputs and outputs from these tool invocations to the build variables
SECONDARY_FLASH += \
??.hex 

SECONDARY_BIN += \
??.bin 

SECONDARY_SIZE += \
??.siz 


#All Target 
all:??.elf ??_debug.elf secondary-outputs


#Tool Invocations
 ??.elf: $(OBJS) $(USER_OBJS) 
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C Linker'
	riscv64-unknown-elf-gcc -march=rv32im -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -O0 -ffunction-sections -fdata-sections  -g3  -T"C:/Users/Administrator/.robei_workspace/projects/??/robei_sdk/env/robei/flash.lds" -nostartfiles -Xlinker --gc-sections -L../ -Wl,-Map,"??.map" --specs=nano.specs -Xlinker --defsym=__stack_size=1K -Wl,--start-group -Wl,--end-group -Wl,--wrap=malloc -Wl,--wrap=free -Wl,--wrap=open -Wl,--wrap=lseek -Wl,--wrap=read             -Wl,--wrap=write -Wl,--wrap=fstat -Wl,--wrap=stat -Wl,--wrap=close -Wl,--wrap=link -Wl,--wrap=unlink -Wl,--wrap=execve             -Wl,--wrap=fork -Wl,--wrap=getpid -Wl,--wrap=kill -Wl,--wrap=wait -Wl,--wrap=isatty -Wl,--wrap=times -Wl,--wrap=sbrk             -Wl,--wrap=_exit -Wl,--wrap=puts -Wl,--wrap=_malloc -Wl,--wrap=_free -Wl,--wrap=_open -Wl,--wrap=_lseek -Wl,--wrap=_read             -Wl,--wrap=_write -Wl,--wrap=_fstat -Wl,--wrap=_stat -Wl,--wrap=_close -Wl,--wrap=_link -Wl,--wrap=_unlink -Wl,--wrap=_execve             -Wl,--wrap=_fork -Wl,--wrap=_getpid -Wl,--wrap=_kill -Wl,--wrap=_wait -Wl,--wrap=_isatty -Wl,--wrap=_times -Wl,--wrap=_sbrk             -Wl,--wrap=__exit -Wl,--wrap=_puts -o "??.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '


 ??_debug.elf: $(OBJS) $(USER_OBJS) 
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C Linker'
	riscv64-unknown-elf-gcc -march=rv32im -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -O0 -ffunction-sections -fdata-sections  -g3  -T"C:/Users/Administrator/.robei_workspace/projects/??/robei_sdk/env/robei/flash_debug.lds" -nostartfiles -Xlinker --gc-sections -L../ -Wl,-Map,"??_debug.map" --specs=nano.specs -Xlinker --defsym=__stack_size=1K -Wl,--start-group -Wl,--end-group -Wl,--wrap=malloc -Wl,--wrap=free -Wl,--wrap=open -Wl,--wrap=lseek -Wl,--wrap=read             -Wl,--wrap=write -Wl,--wrap=fstat -Wl,--wrap=stat -Wl,--wrap=close -Wl,--wrap=link -Wl,--wrap=unlink -Wl,--wrap=execve             -Wl,--wrap=fork -Wl,--wrap=getpid -Wl,--wrap=kill -Wl,--wrap=wait -Wl,--wrap=isatty -Wl,--wrap=times -Wl,--wrap=sbrk             -Wl,--wrap=_exit -Wl,--wrap=puts -Wl,--wrap=_malloc -Wl,--wrap=_free -Wl,--wrap=_open -Wl,--wrap=_lseek -Wl,--wrap=_read             -Wl,--wrap=_write -Wl,--wrap=_fstat -Wl,--wrap=_stat -Wl,--wrap=_close -Wl,--wrap=_link -Wl,--wrap=_unlink -Wl,--wrap=_execve             -Wl,--wrap=_fork -Wl,--wrap=_getpid -Wl,--wrap=_kill -Wl,--wrap=_wait -Wl,--wrap=_isatty -Wl,--wrap=_times -Wl,--wrap=_sbrk             -Wl,--wrap=__exit -Wl,--wrap=_puts -o "??_debug.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
??.hex: ??.elf
	@echo 'Invoking: GNU RISC-V Cross Create Flash Image'
	riscv64-unknown-elf-objcopy -O ihex "??.elf"  "??.hex"
	@echo 'Finished building: $@'
	@echo ' '
??.bin: ??.elf
	@echo 'Invoking: GNU RISC-V Cross Create Bin Image'
	riscv64-unknown-elf-objcopy -O binary "??.elf"  "??.bin"
	@echo 'Finished building: $@'
	@echo ' '
??.siz: ??.elf
	@echo 'Invoking: GNU RISC-V Cross  Print Size'
	riscv64-unknown-elf-size --format=berkeley "??.elf"  
	@echo 'Finished building: $@'
	@echo ' '
# Other Targets
clean:
	 -$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_BIN)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) ??.elf  ??_debug.elf
	-@echo ' '


rebuild:clean all
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_BIN) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ./Demo/makefile.targets
-include ./Demo/makefile.defs
-include ./Demo/makefile.init