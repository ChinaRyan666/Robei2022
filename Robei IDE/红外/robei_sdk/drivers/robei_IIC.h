#ifndef _HAMSTER_IIC_H_
#define _HAMSTER_IIC_H_
#include "config.h"
#ifdef RO_IIC_MODULE_ENABLED
typedef struct
{
	volatile uint32_t IIC_CTL;	
	volatile uint32_t IIC_ADDR2;
	volatile uint32_t IIC_MONITOR;
	volatile uint32_t NULL1;
	volatile uint32_t IIC_PRESCALER;
	volatile uint32_t NULL2;
	volatile uint32_t IIC_INTER_STATE;
	volatile uint32_t IIC_CLEAR;
	volatile uint32_t IIC_INT_CLEAR;
	volatile uint32_t IIC_RX_DATA0;
	volatile uint32_t IIC_RX_DATA1;
	volatile uint32_t IIC_RX_DATA2;
	volatile uint32_t IIC_RX_DATA3;
	volatile uint32_t IIC_TX_DATA0;
	volatile uint32_t IIC_TX_DATA1;
	volatile uint32_t IIC_TX_DATA2;
	volatile uint32_t IIC_TX_DATA3;
}IIC_TypeDef;

/* Register offsets */

#define IIC_CTL				0x00
#define IIC_ADDR			0x04
#define IIC_MONITOR			0x08
#define IIC_PRESCALER		0x10			
#define IIC_IT_STATE		0x18
#define IIC_CLEAR			0x1c
#define IIC_INT_CLEAR		0x20
#define IIC_RX_DATA0		0x24
#define IIC_RX_DATA1		0x28
#define IIC_RX_DATA2		0x2c
#define IIC_RX_DATA3		0x30
#define IIC_TX_DATA0		0x34
#define IIC_TX_DATA1		0x38
#define IIC_TX_DATA2		0x3c
#define IIC_TX_DATA3		0x40

/* Fields */

#define TXIE(x)		(((x) & 0x1) << 1) 
#define RXIE(x)		(((x) & 0x1) << 2) 
#define ADRIE(x)	(((x) & 0x1) << 3) 
#define NACKIE(x)	(((x) & 0x1) << 4) 
#define STOIE(x)	(((x) & 0x1) << 5) 
#define TCIE(x)		(((x) & 0x1) << 6) 
#define ERRIE(x)	(((x) & 0x1) << 7) 
#define IPF(x)		(((x) & 0x1) << 10) 
#define PTCS(x)		(((x) & 0x1) << 11) 
#define ACKEN(x)	(((x) & 0x1) << 12) 
#define TDMAE(x)	(((x) & 0x1) << 14) 
#define RDMAE(x)	(((x) & 0x1) << 15) 
#define SBC(x)		(((x) & 0x1) << 16) 
#define SMBHEN(x)	(((x) & 0x1) << 20) 
#define ALERTEN(x)	(((x) & 0x1) << 22) 
#define PECEN(x)	(((x) & 0x1) << 23) 

#define ADDR(x)	(((x) & 0x3ff) <<0) 
#define RDWRN(x)	(((x) & 0x1) << 10) 
#define ADD10(x)	(((x) & 0x1) << 11) //1： 10bit  0 ：8bit 要看外设
#define START(x)	(((x) & 0x1) << 13) 
#define STOP(x)	(((x) & 0x1) << 14) 
#define NACK(x)	(((x) & 0x1) << 15) 
#define NBYTE(x)	(((x) & 0xff) << 16) 
#define RELOAD(x)	(((x) & 0x1) << 24) 
#define AUTOEND(x)	(((x) & 0x1) << 25) 
#define PECBYTE(x)	(((x) & 0x1) << 26) 

#define MSCKEN(x)	(((x) & 0x1) << 1) 
#define MONEN(x)	(((x) & 0x1) << 3) 

#define SELDEL(x)	(((x) & 0x1ff) << 0) 
#define TCPR(x)	(((x) & 0xf) << 28) 

#define OE(x)	(((x) & 0x1) << 10) 


void Ro_IIC_Init(void);
void Ro_IIC_Write(uint8_t addr,uint8_t data,uint8_t len);
void Ro_IIC_Write_IT(uint8_t addr,uint8_t data);
uint32_t Ro_IIC_Read(uint8_t addr,uint8_t len);
void Ro_IIC_Setup(uint8_t addr,uint8_t len,uint8_t isRead);

#endif
#endif
