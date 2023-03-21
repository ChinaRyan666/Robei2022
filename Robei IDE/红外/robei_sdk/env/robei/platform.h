// See LICENSE for license details.

#ifndef _ROBEI_PLATFORM_H
#define _ROBEI_PLATFORM_H

// Some things missing from the official encoding.h
#define MCAUSE_INT         0x80000000
#define MCAUSE_CAUSE       0x7FFFFFFF

#include "const.h"


/****************************************************************************
 * Platform definitions
 *****************************************************************************/

// Memory map
// 20200327 modified for last system start
//clock setting:
#define POWER_CLK_ADDR _AC(0xfffe0000,UL)
// 20200327 modified for last system end




#define MASKROM_MEM_ADDR _AC(0x00001000,UL)
#define TRAPVEC_TABLE_CTRL_ADDR _AC(0x00001010,UL)
#define OTP_MEM_ADDR _AC(0x00020000,UL)
#define CLINT_CTRL_ADDR _AC(0x02000000,UL)
#define PLIC_CTRL_ADDR _AC(0xFFFE1000,UL)
#define PLIC1_CTRL_ADDR _AC(0xFFFE1000,UL)
#define AON_CTRL_ADDR _AC(0x10000000,UL)
#define PRCI_CTRL_ADDR _AC(0x10008000,UL)
#define OTP_CTRL_ADDR _AC(0x10010000,UL)
#define GPIO_CTRL_ADDR _AC(0xFFFE8000,UL)//vino 20190717 modefied for hamster ip 
#define UART0_CTRL_ADDR _AC(0xfffe9000,UL)
#define SPI0_CTRL_ADDR _AC(0xfffeC000,UL)
#define SPI1_CTRL_ADDR _AC(0xfffdf000,UL)
#define SPI2_CTRL_ADDR _AC(0xfffeb000,UL)
#define SPI0_RW_ADDR _AC(0x00400000,UL)
#define SPI1_RW_ADDR _AC(0x66000000,UL)
#define SPI2_RW_ADDR _AC(0x10000000,UL)
#define PWM0_CLCK_ADDR _AC(0xfffe0c30,UL)
//#define UART1_CTRL_ADDR _AC(0x10023000,UL)
#define UART1_CTRL_ADDR _AC(0xfffea000,UL)
//#define SPI1_CTRL_ADDR _AC(0xfffeb000,UL)
#define TIM0_BASE_ADDR _AC(0xFFFE6000,UL)
//#define SPI2_CTRL_ADDR _AC(0xfffec000,UL) 

#define TIM1_BASE_ADDR _AC(0xFFFE5000,UL)
#define TIM2_BASE_ADDR _AC(0xfffdc000,UL)
#define TIM3_BASE_ADDR _AC(0xfffdd000,UL)
#define TIM4_BASE_ADDR _AC(0xfffde000,UL)

#define SPI0_MEM_ADDR _AC(0x20000000,UL)
#define MEM_CTRL_ADDR _AC(0x80000000,UL)
#define DMA0_CTRL_ADDR _AC(0xfffb0000,UL)
#define DMA1_CTRL_ADDR _AC(0xfffc0000,UL)
#define DMA_CLK_ADDR _AC(0xfffe0000,UL)
#define IWDG_ADDR _AC(0xfffe0000,UL)
#define IIC_BASE_ADDR _AC(0xfffee000,UL)
#define IIS_ADDR _AC(0xFFFED000,UL)
#define MEMIO_ADDR _AC(0x10400000,UL)
#define MEMIO_BREGADDR _AC(0x11000000,UL)

#define MEMIO_L_ADDR _AC(0x65F80000,UL)
#define MEMIO_R_ADDR _AC(0x65F88000,UL)
#define POINT_D_ADDR _AC(0xFFFFFF00,UL)
#define MPU_RW_ADDR _AC(0xfffe4000,UL)
#define HDMI_BASE_ADDR _AC(0xfffe2000,UL)

#define SDRAM_BASE_ADDR _AC(0xfffa0000,UL)
#define SDRAM_MAP_ADDR _AC(0x30000000,UL)

// IOF masks
#define IOF0_SPI1_MASK          _AC(0x000007FC,UL)
#define SPI11_NUM_SS     (4)
#define IOF_SPI1_SS0          (2u)
#define IOF_SPI1_SS1          (8u)
#define IOF_SPI1_SS2          (9u)
#define IOF_SPI1_SS3          (10u)
#define IOF_SPI1_MOSI         (3u)
#define IOF_SPI1_MISO         (4u)
#define IOF_SPI1_SCK          (5u)
#define IOF_SPI1_DQ0          (3u)
#define IOF_SPI1_DQ1          (4u)
#define IOF_SPI1_DQ2          (6u)
#define IOF_SPI1_DQ3          (7u)

#define IOF0_SPI2_MASK          _AC(0xFC000000,UL)
#define SPI2_NUM_SS       (1)
#define IOF_SPI2_SS0          (26u)
#define IOF_SPI2_MOSI         (27u)
#define IOF_SPI2_MISO         (28u)
#define IOF_SPI2_SCK          (29u)
#define IOF_SPI2_DQ0          (27u)
#define IOF_SPI2_DQ1          (28u)
#define IOF_SPI2_DQ2          (30u)
#define IOF_SPI2_DQ3          (31u)

//#define IOF0_I2C_MASK          _AC(0x00003000,UL)

#define IOF0_UART0_MASK         _AC(0x00030000, UL)
#define IOF_UART0_RX   (16u)
#define IOF_UART0_TX   (17u)

#define IOF0_UART1_MASK         _AC(0x03000000, UL)
#define IOF_UART1_RX (24u)
#define IOF_UART1_TX (25u)

#define IOF1_PWM0_MASK          _AC(0x0000000F, UL)
#define IOF1_PWM1_MASK          _AC(0x00780000, UL)
#define IOF1_PWM2_MASK          _AC(0x00003C00, UL)

// Interrupt numbers
#define INT_RESERVED 0
#define INT_WDOGCMP 1
#define INT_RTCCMP 2
#define INT_UART0_BASE 3
#define INT_UART1_BASE 4
#define INT_SPI0_BASE 5
#define INT_SPI1_BASE 6
#define INT_SPI2_BASE 7
#define INT_GPIO_BASE 8
#define INT_PWM0_BASE 40
#define INT_PWM1_BASE 44
#define INT_PWM2_BASE 48

// Helper functions
#define _REG32(p, i) (*(volatile uint32_t *) ((p) + (i)))
#define _REG16(p, i) (*(volatile uint16_t *) ((p) + (i)))
#define _REG32P(p, i) ((volatile uint32_t *) ((p) + (i)))
#define AON_REG(offset) _REG32(AON_CTRL_ADDR, offset)
#define CLINT_REG(offset) _REG32(CLINT_CTRL_ADDR, offset)
#define GPIO_REG(offset) _REG32(GPIO_CTRL_ADDR, offset)
#define OTP_REG(offset)  _REG32(OTP_CTRL_ADDR, offset)
#define PLIC_REG(offset) _REG32(PLIC_CTRL_ADDR, offset)
#define PRCI_REG(offset) _REG32(PRCI_CTRL_ADDR, offset)
#define PWM0_CLK_REG(offset) _REG32(PWM0_CLCK_ADDR, offset)

#define PWM0_REG(offset) _REG32(TIM0_BASE_ADDR, offset)//TIMER32 0
#define PWM1_REG(offset) _REG32(TIM1_BASE_ADDR, offset)//TIMER16 0
#define PWM2_REG(offset) _REG32(TIM2_BASE_ADDR, offset)//TIMER16 1
#define PWM3_REG(offset) _REG32(TIM3_BASE_ADDR, offset)//TIMER16 2
#define PWM4_REG(offset) _REG32(TIM4_BASE_ADDR, offset)//TIMER16 3

#define SPI0_REG(offset) _REG32(SPI0_CTRL_ADDR, offset)
#define SPI0_RW_REG(offset) _REG32(SPI0_RW_ADDR, offset)

#define SPI1_REG(offset) _REG32(SPI1_CTRL_ADDR, offset)
#define SPI1_RW_REG(offset) _REG32(SPI1_RW_ADDR, offset)
#define SPI2_RW_REG(offset) _REG32(SPI2_RW_ADDR, offset)
#define SPI2_REG(offset) _REG32(SPI2_CTRL_ADDR, offset)
#define UART0_REG(offset) _REG32(UART0_CTRL_ADDR, offset)
#define UART1_REG(offset) _REG32(UART1_CTRL_ADDR, offset)
#define DMA0_REG(offset) _REG32(DMA0_CTRL_ADDR, offset)
#define DMA1_REG(offset) _REG32(DMA1_CTRL_ADDR, offset)
#define DMA_CLK_REG(offset) _REG32(DMA_CLK_ADDR, offset)
#define IWDG_REG(offset) _REG32(IWDG_ADDR, offset)
#define IIC_REG(offset) _REG32(IIC_BASE_ADDR, offset)
#define IIS_REG(offset) _REG32(IIC_BASE_ADDR, offset)
#define MEMIO_REG(offset) _REG32(MEMIO_ADDR, offset)
#define MEMIO_BREG(offset) _REG32(MEMIO_BREGADDR, offset)
#define MEMIOD_REG(offset) _REG32(MEMIO_L_ADDR, offset)
#define MEMIOL_REG(offset) _REG32(MEMIO_L_ADDR, offset)
#define MEMIOR_REG(offset) _REG32(MEMIO_R_ADDR, offset)
#define POINT_REG(offset) _REG32(POINT_D_ADDR, offset)
#define MPU_REG(offset) _REG32(MPU_RW_ADDR, offset)
#define HDMI_REG(offset) _REG32(HDMI_BASE_ADDR, offset)

#define SDRAM_REG(offset) _REG32(SDRAM_BASE_ADDR, offset)
#define SDRAM_ADDR(offset) _REG32(SDRAM_MAP_ADDR, offset)
#define SDRAM_U16_REG(offset) _REG16(SDRAM_BASE_ADDR, offset)
#define SDRAM_U16_ADDR(offset) _REG16(SDRAM_MAP_ADDR, offset)



// 20200327 modified for last system start
//clock setting:
#define POWER_CLK_REG(offset) _REG32(POWER_CLK_ADDR, offset)

// 20200327 modified for last system end

#if defined ( __GNUC__ ) && !defined (__CC_ARM) /* GNU Compiler */
#ifndef __weak
#define __weak   __attribute__((weak))
#endif /* __weak */
#ifndef __packed
#define __packed __attribute__((__packed__))
#endif /* __packed */
#endif /* __GNUC__ */

#define UNUSED(X) (void)X      /* To avoid gcc/g++ warnings */


// Misc

#include <stdint.h>

#define NUM_GPIO 32

#define PLIC_NUM_INTERRUPTS 52
#define PLIC_NUM_PRIORITIES 7



unsigned long get_cpu_freq(void);
unsigned long get_timer_freq(void);
uint64_t get_timer_value(void);

#endif /* _SIFIVE_PLATFORM_H */
