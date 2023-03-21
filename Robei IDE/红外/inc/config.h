#ifndef RO_CONFIG_H
#define RO_CONFIG_H
#include "platform.h"
#include "sys.h"


#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

//MODULE_ENABLE
#define RO_IWDG_MODULE_ENABLED
#define RO_WWDG_MODULE_ENABLED
#define RO_DMA_MODULE_ENABLED
#define RO_GPIO_MODULE_ENABLED
#define RO_IIC_MODULE_ENABLED
#define RO_IT_MODULE_ENABLED
#define RO_MEMIO_MODULE_ENABLED
#define RO_PWM_MODULE_ENABLED
#define RO_RTC_MODULE_ENABLED
#define RO_SPI_MODULE_ENABLED
#define RO_TIM32_MODULE_ENABLED
#define RO_TIM16_MODULE_ENABLED
#define RO_UART_MODULE_ENABLED
#define RO_MPU_MODULE_ENABLED
#define RO_FREERTOS_MODULE_ENABLED

#include "robei_SYSCLK.h"

#ifdef RO_IWDG_MODULE_ENABLED
 #include "robei_IWDG.h"
#endif /* RO_IWDG_MODULE_ENABLED */

#ifdef RO_WWDG_MODULE_ENABLED
 #include "robei_WWDG.h"
#endif /* RO_WWDG_MODULE_ENABLED */

#ifdef RO_DMA_MODULE_ENABLED
 #include "robei_DMA.h"
#endif /* RO_DMA_MODULE_ENABLED */

#ifdef RO_GPIO_MODULE_ENABLED
 #include "robei_GPIO.h"
#endif /* RO_GPIO_MODULE_ENABLED */

#ifdef RO_IIC_MODULE_ENABLED
 #include "robei_IIC.h"
#endif /* RO_IIC_MODULE_ENABLED */

#ifdef RO_IT_MODULE_ENABLED
 #include "robei_IT.h"
#endif /* RO_IIS_MODULE_ENABLED */

#ifdef RO_MEMIO_MODULE_ENABLED
 #include "robei_MEMIO.h"
#endif /* RO_MEMIO_MODULE_ENABLED */


#ifdef RO_RTC_MODULE_ENABLED
 #include "robei_RTC.h"
#endif /* RO_RTC_MODULE_ENABLED */

#ifdef RO_SPI_MODULE_ENABLED
 #include "robei_SPI.h"
#endif /* RO_SPI_MODULE_ENABLED */

#ifdef RO_TIM16_MODULE_ENABLED
 #include "robei_TIM16.h"
#endif /* RO_TIM_MODULE_ENABLED */
#ifdef RO_TIM32_MODULE_ENABLED
 #include "robei_TIM32.h"
#endif /* RO_TIM_MODULE_ENABLED */

#ifdef RO_UART_MODULE_ENABLED
 #include "robei_UART.h"
#endif /* RO_UART_MODULE_ENABLED */

//user demo start +++
#include "robei_SYSCLK.h"

#ifdef RO_MPU_MODULE_ENABLED
 #include "robei_MPU.h"
#endif /* RO_MPU_MODULE_ENABLED */


#define RO_MODULE_TEST_UART0 
//#define RO_MODULE_TEST_UART1 
//#define RO_MODULE_TEST_SPI0 
//#define RO_MODULE_TEST_SPI1 
//#define RO_MODULE_TEST_MEMIO 
//#define RO_MODULE_TEST_GPIO
//#define RO_MODULE_TEST_CRASH_CALLBACK 
//#define RO_MODULE_TEST_TIM32 
//#define RO_MODULE_TEST_TIM16 
//#define RO_MODULE_TEST_MPU
//#define RO_MODULE_TEST_IWDG
//#define RO_MODULE_TEST_WWDG
#define RO_MODULE_TEST_HDMI 
#define RO_MODULE_TEST_IIC 




//user demo end ---



#endif /* RO_CONFIG_H */
