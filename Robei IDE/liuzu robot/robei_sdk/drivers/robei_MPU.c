/**
 * @file	hamster_MPU.c
 * @brief	内存保护单元
 *
 * \n
 * @details	
 *
 * \n
 * @version	
 * @author		vinolee
 * @date		2020-7-10
 *
 *
 */

#include "config.h"

#include "platform.h"

#ifdef RO_MPU_MODULE_ENABLED

/**
 * 
 * @brief	
 * \n
 *
 * @param	Addr	要保护的地址	
 * @param	Area	存放保存数据的地址
 * 					@arg MPU_AREA1
 * 					@arg MPU_AREA2
 * 					@arg MPU_AREA3
 * 					@arg MPU_AREA4
 * 					@arg MPU_AREA5
 * 					@arg MPU_AREA6
 * 					@arg MPU_AREA7
 * @param	size	需要保护的大小
 *					@arg MPU_4K
 *				    @arg MPU_8K
 *				    @arg MPU_16K
 *				    @arg MPU_32K
 *				    @arg MPU_64K
 *				    @arg MPU_128K
 *				    @arg MPU_256K
 *				    @arg MPU_512K
 *				    @arg MPU_1M
 *				    @arg MPU_2M
 *				    @arg MPU_4M
 *				    @arg MPU_8M
 *				    @arg MPU_16M
 *				    @arg MPU_32M
 *				    @arg MPU_64M
 *					@arg MPU_128M
 *					@arg MPU_256M
 *					@arg MPU_512M
 *					@arg MPU_1G
 *					@arg MPU_2G
 *					@arg MPU_4G
 * @param	type	允许的操作
 *					@arg MPU_UNRW	不允许读写
 *					@arg MPU_ONLYR	只允许读
 *					@arg MPU_ONLYW	只允许写
 *					@arg MPU_RW		允许读写
 * @retval	None
 * \n
 */
void Ro_MPU_Setup(uint32_t Addr,uint32_t Area,uint8_t size,uint8_t type)
{
	WRITE_REG(MPU_REG(Area),AREA_BASE(Addr>>12)|AREA_PSIZE(size)|AREA_AE(1));
	switch(Area)
	{
		case MPU_AREA1:
			MODIFY_REG(MPU_REG(MPU_DAP),AP1(MPU_RW),AP1(type));
			break;
		case MPU_AREA2:
			MODIFY_REG(MPU_REG(MPU_DAP),AP2(MPU_RW),AP2(type));
			break;
		case MPU_AREA3:
			MODIFY_REG(MPU_REG(MPU_DAP),AP3(MPU_RW),AP3(type));
			break;
		case MPU_AREA4:
			MODIFY_REG(MPU_REG(MPU_DAP),AP4(MPU_RW),AP4(type));
			break;
		case MPU_AREA5:
			MODIFY_REG(MPU_REG(MPU_DAP),AP5(MPU_RW),AP5(type));
			break;
		case MPU_AREA6:
			MODIFY_REG(MPU_REG(MPU_DAP),AP6(MPU_RW),AP6(type));
			break;
		case MPU_AREA7:
			MODIFY_REG(MPU_REG(MPU_DAP),AP7(MPU_RW),AP7(type));
			break;
		default:
			break;

	}
	WRITE_REG(MPU_REG(MPU_SCON),MMUEN(1)|ALIGN(1)|BENDEN(0));
}



#endif
