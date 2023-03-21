#ifndef _HAMSTER_MPU_H_
#define _HAMSTER_MPU_H_


#define MPU_SCON		(0x0180)
#define MPU_DAP			(0x0580)

#define MPU_AREA1		(0x0684)
#define MPU_AREA2		(0x0688)
#define MPU_AREA3		(0x068c)
#define MPU_AREA4		(0x0690)
#define MPU_AREA5		(0x0694)
#define MPU_AREA6		(0x0698)
#define MPU_AREA7		(0x069c)

/* Fields */
#define MMUEN(x)    (((x) & 0x1) << 0) 
#define ALIGN(x)    (((x) & 0x1) << 2) 
#define BENDEN(x)    (((x) & 0x1) << 7) 
#define SYSEN(x)    (((x) & 0x1) << 8) 
#define ROMEN(x)    (((x) & 0x1) << 9) 
#define HEVEN(x)    (((x) & 0x1) << 13) 

#define AP0(x)    (((x) & 0x3) << 0) 
#define AP1(x)    (((x) & 0x3) << 2) 
#define AP2(x)    (((x) & 0x3) << 4) 
#define AP3(x)    (((x) & 0x3) << 6) 
#define AP4(x)    (((x) & 0x3) << 8) 
#define AP5(x)    (((x) & 0x3) << 10) 
#define AP6(x)    (((x) & 0x3) << 12) 
#define AP7(x)    (((x) & 0x3) << 14) 

#define AREA_AE(x)    (((x) & 0x1) << 0) 
#define AREA_PSIZE(x)    (((x) & 0x1f) << 1) 
#define AREA_BASE(x)    (((x) & 0xfffff) << 12)


#define MPU_UNRW	0x00
#define MPU_ONLYR	0x01
#define MPU_ONLYW	0x02
#define MPU_RW		0x03


#define MPU_4K		0x0B
#define MPU_8K		0x0C
#define MPU_16K		0x0D
#define MPU_32K		0x0E
#define MPU_64K		0x0F
#define MPU_128K	0x10
#define MPU_256K	0x11
#define MPU_512K	0x12
#define MPU_1M		0x13
#define MPU_2M		0x14
#define MPU_4M		0x15
#define MPU_8M		0x16
#define MPU_16M		0x17
#define MPU_32M		0x18
#define MPU_64M		0x19
#define MPU_128M	0x1A
#define MPU_256M	0x1B
#define MPU_512M	0x1C
#define MPU_1G		0x1D
#define MPU_2G		0x1E
#define MPU_4G		0x1F

void Ro_MPU_Setup(uint32_t Addr,uint32_t Area,uint8_t size,uint8_t type);

#endif

