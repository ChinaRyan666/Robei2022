// See LICENSE for license details.
#include <smp.h>
#include "stack.s"

.section .init
.global _start

.type _start,@function
//.equ  Clock_Select0   ,      0x0a12188c #; speed sclk[2:1]=2, ahb[6:3]=hclkd2=1, adp[10:7]=hclkd2=1, apb[18:15]=pclkd5=4, ssp[26:23]=pclkd5=4, systck[30:27]=hclkd2=1
.equ  Clock_Select0		,	 0x0890988c #; speed sclk[2:1]=2, ahb[6:3]=hclkd2=1, adp[10:7]=hclkd2=1, apb[18:15]=pclkd5=4, ssp[26:23]=pclkd5=4, systck[30:27]=hclkd2=1
.equ  Clock_Select0s  ,      0x0991989c//0x0b13188c #; speed sclk[2:1]=2, ahb[6:3]=hclkd2=1, adp[10:7]=hclkd2=1, apb[18:15]=pclkd5=4, ssp[26:23]=pclkd5=4, systck[30:27]=hclkd2=1
.equ  Clock_Select0u  ,      0x1c94999c #; speed sclk[2:1]=2, ahb[6:3]=hclkd4=3, adp[10:7]=hclkd4=3, apb[18:15]=pclkd16=9, ssp[26:23]=pclkd16=9, systck[30:27]=hclkd4=3
.equ  UART_Clock_Sel  ,      0x0440499a #; set uart clk_sel[11:8]= gclk/16=9
.equ  SysTick_Control ,      0x00000002 #; clk_src[2]=0, stick_init[1]=1, stick_en[0]=1

_start:
#;Vectors
	j Reset_Handler          	#pc=0, no tail
	mret #jalr ra,ra,0       	#pc=4
	mret #jalr ra,ra,0      	#pc=8
	mret                     	#pc=c
	j	crash_Handler           #pc=10
	mret                      	#pc=14
	mret                     	#pc=18
	j	FIRQ0_Handler			#pc=1c, fiq
	j	IRQ0_Handler      		#pc=20
	mret                     	#pc=24
	mret                     	#pc=28
	mret                     	#pc=2c
	mret                     	#pc=30
	j	irq5_Handler            #pc=34
	j	irq6_Handler            #pc=38
	j	irq7_Handler            #pc=3c
	j	irq8_Handler            #pc=40
	j	irq9_Handler            #pc=44
	j	irq10_Handler           #pc=48
	j	irq11_Handler			#pc=4c
	j	irq12_Handler     		#pc=50
	j	irq13_Handler           
	j	irq14_Handler
	j	irq15_Handler
	j	irq16_Handler
	j	irq17_Handler
	j	irq18_Handler
	j	irq19_Handler
	j	irq20_Handler
	j	irq21_Handler
	j	irq22_Handler     		#;					,pc=78
	j	irq23_Handler 			#;0X20, irq23  		,pc=7c
	j	irq24_Handler 			#;0X24, irq24 		,pc=80
	j	IRQ_Handler 			#;0X28, irq25 		,pc=84
	j	IRQ_Handler 			#;0X2C, irq26 		,pc=88
	j	IRQ_Handler 			#;0X30, irq27 		,pc=8c
	j	irq28_Handler 			#;0X34, irq28 		,pc=90
	j	IRQ_Handler 			#;0X38, irq29 		,pc=94
	j	IRQ_Handler 			#;0X38, irq30 		,pc=98
	j	irq31_Handler     		#;0X38, irq31 		,pc=9c
.macro push_in_ra
	addi	sp,sp,-4
	sw		ra,0(sp)
.endm
.macro push_out_ra
	lw		ra,0(sp)
	addi	sp,sp,4
.endm

push_in_Stack:
	addi	 sp,sp,-120
	sw  tp,4(sp)
	sw  t0,8(sp)
	sw  t1,12(sp)
	sw  t2,16(sp)
	sw  s0,20(sp)
	sw  s1,24(sp)
	sw  a0,28(sp)
	sw  a1,32(sp)
	sw  a2,36(sp)
	sw  a3,40(sp)
	sw  a4,44(sp)
	sw  a5,48(sp)
	sw  a6,52(sp)
	sw  a7,56(sp)
	sw  s2,60(sp)
	sw  s3,64(sp)
	sw  s4,68(sp)
	sw  s5,72(sp)
	sw  s6,76(sp)
	sw  s7,80(sp)
	sw  s8,84(sp)
	sw  s9,88(sp)
	sw  s10,92(sp)
	sw  s11,96(sp)
	sw  t3,100(sp)
	sw  t4,104(sp)
	sw  t5,108(sp)
	sw  t6,112(sp)
	jr	  ra
push_out_Stack:
	lw  tp,4(sp)
	lw  t0,8(sp)
	lw  t1,12(sp)
	lw  t2,16(sp)
	lw  s0,20(sp)
	lw  s1,24(sp)
	lw  a0,28(sp)
	lw  a1,32(sp)
	lw  a2,36(sp)
	lw  a3,40(sp)
	lw  a4,44(sp)
	lw  a5,48(sp)
	lw  a6,52(sp)
	lw  a7,56(sp)
	lw  s2,60(sp)
	lw  s3,64(sp)
	lw  s4,68(sp)
	lw  s5,72(sp)
	lw  s6,76(sp)
	lw  s7,80(sp)
	lw  s8,84(sp)
	lw  s9,88(sp)
	lw  s10,92(sp)
	lw  s11,96(sp)
	lw  t3,100(sp)
	lw  t4,104(sp)
	lw  t5,108(sp)
	lw  t6,112(sp)
	addi	 sp,sp,120
	jr	  ra

Reset_Handler:
	li	ra,0
	li	tp,0
	li	t0,0
	li	t1,0
	li	t2,0
	li	s0,0
	li	s1,0
	li	a0,0
	li	a1,0
	li	a2,0
	li	a3,0
	li	a4,0
	li	a5,0
	li	a6,0
	li	a7,0
	li	s2,0
	li	s3,0
	li	s4,0
	li	s5,0
	li	s6,0
	li	s7,0
	li	s8,0
	li	s9,0
	li	s10,0
	li	s11,0
	li	t3,0
	li	t4,0
	li	t5,0
	li	t6,0
	.option push
	.option norelax
		la gp, __global_pointer$
	.option pop
		la sp, _sp
		macro_InitStack
	j TOEND
IRQ_Handler:
	mret
crash_Handler:
	call Ro_Crash_IRQHandle
	mret
FIRQ0_Handler:	
	push_in_ra
	jal push_in_Stack
	call Ro_WWDG_IRQHandle
	jal push_out_Stack
	push_out_ra

mret
IRQ0_Handler: #for systick
#ifdef HAMSTER_MODULE_TEST_RTOS
    push_in_ra
     jal push_in_Stack
       /////////////////////////////////////////
     .global pxCurrentTCB
      /* sw mstatus */
     //csrr t0, mstatus //pointer
     //sw t0, 32 * 4(sp)
     /* sw current stackpointer in task control block (TCB) */
     lw t0, pxCurrentTCB //pointer
     sw sp, 0x0(t0)
     csrr t0, mepc
     sw t0, 33 * 4(sp)
    ///////////////////////////////////////////////////////////
     call  vPortSysTickHandler
    ///////////////////////////////////////////////////////////
     .global pxCurrentTCB
     /* lw stack pointer from the current TCB */
     //lw sp, pxCurrentTCB
     //lw sp, 0x0(sp)
     lw t0, pxCurrentTCB
     lw sp, 0x0(t0)
     /* lw task program counter */
     lw t0, 33 * 4(sp)
     csrw mepc, t0
    //-------------------------------------------------
    ///////////////////////////////////////////////////////////////
       jal push_out_Stack
     push_out_ra
#endif
	mret	
irq5_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_GPIO45_IRQHandle
	jal push_out_Stack	
	push_out_ra
 	mret
irq6_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_GPIO6_IRQHandle
	jal push_out_Stack  
	push_out_ra
	mret
irq7_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_GPIO7_IRQHandle
	jal push_out_Stack  
	push_out_ra
	 mret
irq8_Handler:
	push_in_ra
 	jal push_in_Stack
	call Ro_GPIO0_IRQHandle
	jal push_out_Stack	
	push_out_ra
 	mret
irq9_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_GPIO1_IRQHandle
	jal push_out_Stack	
	push_out_ra
	mret
irq10_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_GPIO2_IRQHandle
	jal push_out_Stack	
	push_out_ra
	mret
irq11_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_GPIO3_IRQHandle
	jal push_out_Stack	
	push_out_ra
	mret
irq12_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_DMA0_CH01_IRQHandle
	jal push_out_Stack
	push_out_ra
	mret
irq13_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_DMA1_CH01_IRQHandle
	jal push_out_Stack
	push_out_ra
	mret
irq14_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_DMA01_CH2_IRQHandle
	jal push_out_Stack
	push_out_ra
	mret
irq15_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_DMA01_CH3_IRQHandle
	jal push_out_Stack
	push_out_ra
	mret
irq16_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_DMA01_CH4_IRQHandle
	jal push_out_Stack
	push_out_ra
	mret
irq17_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_DMA01_CH5_IRQHandle
	jal push_out_Stack
	push_out_ra
	mret
irq18_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_DMA01_CH6_IRQHandle
	jal push_out_Stack
	push_out_ra
	mret
irq19_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_TIM16_IRQHandle
    	jal push_out_Stack
    	push_out_ra
	mret
irq20_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_TIM32_IRQHandle
    	jal push_out_Stack
    	push_out_ra
	mret
irq21_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_DMA01_CH7_IRQHandle
	jal push_out_Stack
	push_out_ra
	mret
irq22_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_Adptive_IRQHandle
	jal push_out_Stack
	push_out_ra
	mret
irq23_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_SSP1_IRQHandle
	jal push_out_Stack
	push_out_ra
	mret
irq24_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_UART0_IRQHandle
	jal push_out_Stack
	push_out_ra
	mret
irq25_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_UART1_IRQHandle
	jal push_out_Stack
	push_out_ra
	mret
irq26_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_SSP0_IRQHandle
	jal push_out_Stack
	push_out_ra
	mret
irq27_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_SSP2_IRQHandle
	jal push_out_Stack
	push_out_ra
	mret
irq28_Handler:
	push_in_ra
	jal push_in_Stack
	call Ro_IIC_IRQHandle
	jal push_out_Stack
	push_out_ra
	mret
irq31_Handler:
	mret
TOEND:
	call _start_after_loder
	tail exit 
