#ifndef _HAMSTER_MEMIO_H_
#define _HAMSTER_MEMIO_H_
#include "robei_DMA.h"
#include "config.h"
#ifdef RO_MEMIO_MODULE_ENABLED
 
#define MEM_INDEX0		(0x100000)
#define MEM_INDEX1		(0x100400)
#define MEM_INDEX2		(0x100800)
#define MEM_INDEX3		(0x100C00)
#define MEM_INDEX4		(0x101000)
#define MEM_INDEX5		(0x105000)
#define MEM_INDEX6		(0x106000)
#define MEM_INDEX7		(0x107000)
#define MEM_INDEX8		(0x108000)
#define MEM_INDEX9		(0x109000)
#define MEM_INDEX10		(0x10a000)
#define MEM_INDEX11		(0x10b000)
#define MEM_INDEX12		(0x10c000)
#define MEM_INDEX13		(0x10d000)
#define MEM_INDEX14		(0x10e000)
#define MEM_INDEX15		(0x10f000)

#define MEM_ENABLE		(1)
#define MEM_DISABLE		(0)

#define MEM_IN			(0)
#define MEM_OUT			(1)

 
#define MEM_LEFT_TO_RIGHT		(0)
#define MEM_RIGHT_TO_LEFT		(1)
 
#define MEM_LEFT_IN			(0)
#define MEM_LEFT_OUT		(1)
 


 /* ADP Register offsets */
#define ROCELL00   (0x40000)
#define ROCELL01   (0x40004)
#define ROCELL02   (0x40008)
#define ROCELL03   (0x4000c)

#define ROCELL10   (0x40040)
#define ROCELL11   (0x40044)
#define ROCELL12   (0x40048)
#define ROCELL13   (0x4004c)

#define ROCELL20   (0x40080)
#define ROCELL21   (0x40084)
#define ROCELL22   (0x40088)
#define ROCELL23   (0x4008c)

#define ROCELL30   (0x400c0)
#define ROCELL31   (0x400c4)
#define ROCELL32   (0x400c8)
#define ROCELL33   (0x400cc)

#define BREG00   (0x80000)
#define BREG01   (0x80004)
#define BREG02   (0x80008)
#define BREG03   (0x8000c)

#define BREG10   (0x80040)
#define BREG11   (0x80044)
#define BREG12   (0x80048)
#define BREG13   (0x8004c)

#define BREG20   (0x80080)
#define BREG21   (0x80084)
#define BREG22   (0x80088)
#define BREG23   (0x8008c)

#define BREG30   (0x800c0)
#define BREG31   (0x800c4)
#define BREG32   (0x800c8)
#define BREG33   (0x800cc)

/* ADP  Fields */
#define SELA(x)  (((x) & 0xf) << 0) 
#define SELB(x)  (((x) & 0xf) << 4) 
#define SELC(x)  (((x) & 0xf) << 8) 

#define BUS_V           (0x01)
#define BUS_H           (0x02)
#define BREG            (0x07)
#define BOTTOM          (0x08)
#define RIGHTBOTTOM     (0x09)
#define RIGHT           (0x0a)
#define RIGHTTOP        (0x0b)
#define TOP             (0x0c)
#define LEFTTOP         (0x0d)
#define LEFT            (0x0e)
#define LEFTBOTTOM      (0x0f)
/*
"SEL:
selecta = {SEL[3],SEL[2:0] + ROT}
selectb = {SEL[7],SEL[6:4] + ROT}   
selectc = {SEL[11],SEL[10:8] + ROT}  
selecta选择数据a的方向，selectB选择数据B的方向,selectC选择CO的方向
0001 bus_v
0010 bus_h
0111 breg
1000 bottom
1001 rightbottom
1010 right
1011 righttop
1100 top
1101 lefttop
1110 left
1111 leftbottom
"
*/
#define OP(x)  (((x) & 0x1f) << 12) 
//测试rocell 每个单元都有
#define OP_BYPASS           (0x01)
#define OP_AND              (0x02)
#define OP_OR               (0x03)
#define OP_XOR              (0x04)
#define OP_CMP              (0x05)
#define OP_LEFTSHIFT        (0x06)
#define OP_RIGHTSHIFT       (0x07)
#define OP_INC              (0x08)//OP_CMP20201119晏昼改
#define OP_ABS              (0x09)
#define OP_NEG              (0x0a)
#define OP_UADDR            (0x0c)
#define OP_USUB             (0x0d)
#define OP_SADDSUB          (0x0e)
#define OP_MERGE            (0x0b)
#define OP_CONST            (0x0f)
//测试robu 只有（1,1）有
#define OP_F2I              (0x10)
#define OP_I2F              (0x11)
#define OP_ADD              (0x12)
#define OP_SUB              (0x13)
//测试romuf
#define OP_INT_MUL              (0x14)
#define OP_FLOAT_MUL            (0x15)

/*
OP:
0001 bypass
0010 and
0011 or
0100 xor
0101 LUT
0110 left shift
0111 right shift
1000 cmp
1001 abs
1010 neg
1100 uaddr
1101 usub
1110 saddsub
1011 merge
1111 const
*/

#define SWITCH(x) (((x) & 0x3) << 17) 
/*
SWITCH:These bits are used to check cont
l register for err recover. 
00:no check. 
01: check control register0. 
10: check control register1.
11: check all control registers.
*/

#define ROT(x)  (((x) & 0x7) << 19) 
#define BREG1(x)  (((x) & 0xffffffff) << 0) 

#define COL(x)  (((x) & 0xffff) << 6)//ROW [3:2]
#define ROW(x)  (((x) & 0xf) << 2)//COL [5:2]
#define ROCELL_COL(x)  (((x) & 0x1f) << 22)//ROW [26:22]
#define ROCELL_ROW(x)  (((x) & 0x1f) << 27)//COL [31:27]


/* MEMIO Register offsets */
#define TWI_L			(0x04)
#define TWI_R			(0x0C)
#define MEMORY_C		(0x10)
#define ROW_STATUS		(0x14)


#define REMAP0			(0x1C)
#define REMAP1			(0x20)
#define REMAP2			(0x24)
#define REMAP3			(0x28)
	
#define REMAP4			(0x40)
#define REMAP5			(0x44)
#define REMAP6			(0x48)
#define REMAP7			(0x4c)
#define REMAP8			(0x50)



/* MEMIO  Fields */
#define INDEX(x)		(((x) & 0xf) << 0) 
#define INDEX_COL(x)	(((x) & 0x3) << 0)//COL [1:0]
#define INDEX_ROW(x)	(((x) & 0x3) << 2)//ROW [3:2]

#define INDEX_8(x)		(((x) & 0x7ff) << 0) 
#define INDEX_COL_8(x)	(((x) & 0xff) << 0)//ROW [7:0]
#define INDEX_ROW_8(x)	(((x) & 0x7) << 8)//ROW [11:8]
#define WIDTH_8(x)		(((x) & 0x7ff) << 13) 

#define INDEX_9(x)		(((x) & 0xfff) << 0) 
#define INDEX_COL_9(x)		(((x) & 0xff) << 0)//ROW [7:0]
#define INDEX_ROW_9(x)		(((x) & 0xf) << 8)//ROW [11:8]
#define WIDTH_9(x)		(((x) & 0xfff) << 13)
#define WIDTH(x)		(((x) & 0x7f) << 13) 
#define RECV(x)			(((x) & 0x1) << 29) 
#define FULL(x)			(((x) & 0x1) << 30) 
#define DONE(x)			(((x) & 0x1) << 31) 
//---------memcontrol-----
#define LRCS(x)			(((x) & 0x1) << 0) 
#define LST(x)			(((x) & 0x1) << 1) 
#define MEM_LDMAE(x)		(((x) & 0x1) << 2) 
#define LIRQE(x)		(((x) & 0x1) << 3) 
#define LHORIZON(x)		(((x) & 0x1) << 4) 
#define LVALID(x)		(((x) & 0x1) << 5) 
#define LCTL(x)	(((x) & 0x1) << 6) 

#define RRCS(x)			(((x) & 0x1) << 8) 
#define RST(x)			(((x) & 0x1) << 9) 
#define MEM_RDMAE(x)	(((x) & 0x1) << 10) 
#define RIRQE(x)		(((x) & 0x1) << 11) 
#define RHORIZON(x)		(((x) & 0x1) << 12) 
#define RVALID(x)		(((x) & 0x1) << 13) 
#define RCTL(x)			(((x) & 0x1) << 14) 
//---------memcontrol-----

#define R0(x)			(((x) & 0x1) << 0) 
#define R1(x)			(((x) & 0x1) << 1) 
#define R2(x)			(((x) & 0x1) << 2) 
#define R3(x)			(((x) & 0x1) << 3) 


#define ROW_L(x)		(((x) & 0x3) << 2) 
#define ROW_R(x)		(((x) & 0x3) << 15) 
#define ROW2_L(x)		(((x) & 0x3) << 2) 
#define ROW2_R(x)		(((x) & 0x3) << 15) 
#define ROW3_L(x)		(((x) & 0x3) << 2) 
#define ROW3_R(x)		(((x) & 0x3) << 15) 
#define ROW4_L(x)		(((x) & 0x3) << 2) 
#define ROW4_R(x)		(((x) & 0x3) << 15) 

typedef struct
{               
	uint8_t LRCS; 
	uint8_t LST; 
	uint8_t LDMAE; 
	uint8_t LIRQE; 
	uint8_t LHORIZON; 
	uint8_t LVALID;
	uint8_t LCTL; 

	uint8_t RRCS; 
	uint8_t RST; 
	uint8_t RDMAE; 
	uint8_t RIRQE; 
	uint8_t RHORIZON; 
	uint8_t RVALID; 
	uint8_t RCTL; 
}MEMIO_ControlTypeDef;

void Ro_Adaptive_SetConfig(uint32_t config);
void Ro_Adaptive_MemControlSetup(uint8_t bStart,uint32_t memLeftWay);
void Ro_Adaptive_TWIL_SetUp(uint8_t inout,uint8_t width,uint8_t row,uint8_t col);
void Ro_Adaptive_TWIR_SetUp(uint8_t inout,uint8_t width,uint8_t row,uint8_t col);
void Ro_Adaptive_TWIL8_SetUp(uint8_t inout,uint16_t width,uint8_t row,uint8_t col);
void Ro_Adaptive_TWIR8_SetUp(uint8_t inout,uint16_t width,uint8_t row,uint8_t col);
void Ro_Adaptive_TWIL9_SetUp(uint8_t inout,uint16_t width,uint8_t row,uint8_t col);
void Ro_Adaptive_TWIR9_SetUp(uint8_t inout,uint16_t width,uint8_t row,uint8_t col);

#endif
#endif
