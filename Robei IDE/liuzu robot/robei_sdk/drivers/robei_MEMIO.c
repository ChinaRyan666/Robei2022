/**
 * @file		hamster_MEMIO.c
 * @brief		memio操作接口
 *
 * \n
 * @details	
 *
 * \n
 * @version	
 * @author		vinolee
 * @date		2020-7-10
 *
 * @history	
 *
 */
#include "config.h"

#ifdef RO_MEMIO_MODULE_ENABLED
#include "robei_MEMIO.h"
#include "platform.h"

/**
 * 
 * @brief	初始化adaptive
 * \n
 *
 * @param	none		
 * @retval	None
 * \n
 */


void Ro_Adaptive_Init(void)
{
	Ro_IT_Enable_ADP();
	Ro_Init_ENABLE_ADAPTIVE(1);
}

/**
 * 
 * @brief	配置每个单元
 * \n
 *
 * @param	config	
 *			@note row[31:26]col[25:20]ROT[19]SWITCH[18:17]OP[15:12]C[11:8]B[7:4]A[3:0]
 * @retval	None
 * \n
 */

//void Ro_Adaptive_SetConfig1(uint32_t row,uint32_t col,uint32_t config,bool rocell_b)
//{
  //  int base=rocell_b?Bbase:Rbase;
//	uint8_t row,col;
//	row=(config>>27)&(0x1F);//寄存器在第27位,&0x1f是保留五位
//	col=(config>>22)&(0x1F);//寄存器在第22位，宏定义的时候左移了对应位数，所以需要移动回
//	WRITE_REG(MEMIO_REG(base+row*0x40+col*0x04),config);
//}


void Ro_Adaptive_SetConfig(uint32_t config)
{
	uint8_t row,col;
	row=(config>>27)&(0x1F);//寄存器在第27位,&0x1f是保留五位
	col=(config>>22)&(0x1F);//寄存器在第22位，宏定义的时候左移了对应位数，所以需要移动回
	WRITE_REG(MEMIO_REG(ROCELL00+row*0x40+col*0x04),config);
}
void Ro_Adaptive_ConfigCell(uint32_t row,uint32_t col, uint32_t config)
{
	WRITE_REG(MEMIO_REG(ROCELL00+(row<<6)+(col<<2)),config^1023);
}
void Ro_Adaptive_ConfigBreg(uint32_t row,uint32_t col, uint32_t config)
{
	WRITE_REG(MEMIO_BREG(BREG00+(row<<6)+(col<<2)),config);
}


void Ro_Adaptive_ConfigBusmatrix(uint32_t row, uint32_t config)
{
	if(row<4)
	{
		WRITE_REG(MEMIO_REG(REMAP0+(row<<2)),config);
	}
	else
	{
      WRITE_REG(MEMIO_REG(0x30+(row<<2)),config);
	}
}

/**
 * 
 * @brief	直接加载PC端配置文件
 *
 *
 * @param	uint32_t ConfigAddr 	
 * @note	Config必须是4字节对齐
 * @retval	None
 *
 */
 uint8_t Ro_Adaptive_LoadConfig(uint32_t index)
{
	uint32_t i=12;
	while(((uint32_t)(_REG32(index,i)))!=0xffffffff)
	{
	   _REG32(_REG32(index,i),0)=(uint32_t)(_REG32(index,i+4));
	   
	   printf(" %08X	%08X\r\n",(uint32_t)(_REG32(index,i)),(uint32_t)(_REG32(index,i+4)));
	   i+=8;
	}
	if(i==12)
		return 0;
	else return 1;
}
 #if 0
 /**
 * 
 * @brief	使MEMIO置为使能状态
 *
 *
 * @param	uint32_t index 	
 * @note	当前配置的index
 * @retval	None
 *
 */
 void Ro_MEMIO_CheckReady(uint32_t index)
 {
	 uint32_t a,b;
	 extern uint8_t g_u8AdpIRQFlag;
	 a=READ_REG(MEMIOL_REG(0));
	 b=READ_REG(MEMIOL_REG(0x04));
	 Ro_Adaptive_TWIL9_SetUp(MEM_IN,2,0,0);
	 Ro_Adaptive_TWIR9_SetUp(MEM_OUT,(uint32_t)(_REG32(index,4)),0,0);//ROBU ROMUF 15			 （1）
	 Ro_Adaptive_MemControlSetup(MEM_ENABLE);
	 
	 WRITE_REG(MEMIOL_REG(0x00),a);
	 WRITE_REG(MEMIOL_REG(0x04),b);
	 while(1)
	 {
		 if(g_u8AdpIRQFlag==1)
		 {
			 g_u8AdpIRQFlag=0;
			 break;
		 }
	 }
 }
#endif
#if 0
  /**
 * 
 * @brief	启动Adaptive进行计算
 *
 *
 * @param	uint32_t startCol 	
 *			开始计算列的起始列号
 * @param	uint32_t colLen 	
 *			需要计算多少列
 * @param	uint32_t index 	
 * @note	当前配置的index
 * @retval	None
 *
 */
 void Ro_MEMIO_Restart(uint32_t startCol,uint32_t colLen,uint32_t index)
 {
	 uint32_t a,b;
	 a=READ_REG(MEMIOL_REG(startCol<<6));
	 b=READ_REG(MEMIOL_REG((startCol<<6)+4));	 
	 Ro_Adaptive_MemControlSetup(MEM_ENABLE);
	 Ro_Adaptive_TWIL9_SetUp(MEM_IN,2,0,(colLen-1)<<4);//从0行0列开始 数据的行数 （2） 
	 Ro_Adaptive_TWIR9_SetUp(MEM_OUT,(uint32_t)(_REG32(index,4)),0,0);//ROBU ROMUF 15			 （1）
	 WRITE_REG(MEMIOL_REG(startCol<<6),a);
	 WRITE_REG(MEMIOL_REG((startCol<<6)+4),b);
 }
#endif
 /**
* 
* @brief   启动Adaptive进行计算
*
*
* @param   uint32_t startCol   
*		   开始计算列的起始列号
* @param   uint32_t colLen	   
*		   需要计算多少列
* @param   uint32_t index  
* @param   uint32_t memLeftWay  
*		   设置输入输出方向
* @note    当前配置的index
* @retval  None
*
*/

void Ro_Adaptive_Start(uint32_t startCol,uint32_t colLen,uint32_t index,uint32_t memLeftWay)
{	
	uint32_t a;
	if(memLeftWay==MEM_LEFT_IN)
	{
		a=READ_REG(MEMIOL_REG(startCol<<6));
		WRITE_REG(MEMIOL_REG(startCol<<6),a);
	}
	else
	{
		a=READ_REG(MEMIOR_REG(startCol<<6));
		WRITE_REG(MEMIOR_REG(startCol<<6),a);
	}
	Ro_Adaptive_TWIL9_SetUp(memLeftWay,colLen<<4,0,startCol<<4);
	Ro_Adaptive_TWIR9_SetUp(!memLeftWay,(uint32_t)(_REG32(index,4)),0,0);//ROBU ROMUF 15			（1）
	Ro_Adaptive_MemControlSetup(MEM_ENABLE,memLeftWay);
}

void Ro_Adaptive_MemIOConfig(uint32_t startCol,uint32_t direction)
{	
	Ro_Adaptive_MemControlSetup(MEM_DISABLE,direction);
	if(direction==MEM_LEFT_TO_RIGHT)
		Ro_Adaptive_TWIL9_SetUp(MEM_IN,1,0,startCol<<4);//从0行0列开始 数据的行数 （2） 
	else
		Ro_Adaptive_TWIR9_SetUp(MEM_IN,1,0,startCol<<4);//从0行0列开始 数据的行数 （2） 
}

/**
 * 
 * @brief	写数据
 * \n
 *
 * @param	row 单元行
 * @param	col 单元列
 * @param	data 数据
 *	@note  行列有第三个
 * @retval	None
 * \n
 */

void Ro_Adaptive_WriteData(uint32_t block,uint32_t row,uint32_t col,uint32_t data)
{
	if(block==0)
		MEMIOL_REG(ROW(row)|COL(col))=data;
	else
		MEMIOR_REG(ROW(row)|COL(col))=data;
		
}
/**
 * 
 * @brief	读数据
 * \n
 *
 * @param	row 单元行
 * @param	col 单元列
	
 *	@note  行列有第三个
 * @retval	uint32_t 返回
 * \n
 */

uint32_t Ro_Adaptive_ReadData(uint32_t block,uint32_t row,uint32_t col)
{
	if(block==1)
		return (uint32_t)MEMIOR_REG(ROW(row)|COL(col));
	else
		return (uint32_t)MEMIOL_REG(ROW(row)|COL(col));
}

/**
 * 
 * @brief	设置memio Left memio width and index
 * \n
 *
 * @param	inout 方向
 *			@arg 0，写
 *			@arg 1，读
 * @param	width 宽度，以字为单位
 * @param	index 首位
 *	@note  行列有第三个
 * @retval	None
 * \n
 */

void Ro_Adaptive_TWIL_SetUp(uint8_t inout,uint8_t width,uint8_t row,uint8_t col)
{
	WRITE_REG(MEMIO_REG(TWI_L),DONE(0)|FULL(0)|RECV(inout)|WIDTH(width)|INDEX(INDEX_ROW(row)|INDEX_COL(col)));
	
}
/**
 * 
 * @brief	设置memio Left memio width and index
 * \n
 *
 * @param	inout 方向
 *			@arg 0，写
 *			@arg 1，读
 * @param	width 宽度，以字为单位
 * @param	index 首位
 *	@note  行列有第三个
 * @retval	None
 * \n
 */

void Ro_Adaptive_TWIR_SetUp(uint8_t inout,uint8_t width,uint8_t row,uint8_t col)
{
	WRITE_REG(MEMIO_REG(TWI_R),DONE(0)|FULL(0)|RECV(inout)|WIDTH(width)|INDEX(INDEX_ROW(row)|INDEX_COL(col)));//0x4000c00
}

void Ro_Adaptive_TWIL8_SetUp(uint8_t inout,uint16_t width,uint8_t row,uint8_t col)
{
	WRITE_REG(MEMIO_REG(TWI_L),DONE(0)|FULL(0)|RECV(inout)|WIDTH_8(width)|INDEX_8(INDEX_ROW_8(row)|INDEX_COL_8(col)));
}
void Ro_Adaptive_TWIR8_SetUp(uint8_t inout,uint16_t width,uint8_t row,uint8_t col)
{
	WRITE_REG(MEMIO_REG(TWI_R),DONE(0)|FULL(0)|RECV(inout)|WIDTH_8(width)|INDEX_8(INDEX_ROW_8(row)|INDEX_COL_8(col)));//0x4000c00
}

void Ro_Adaptive_TWIL9_SetUp(uint8_t inout,uint16_t width,uint8_t row,uint8_t col)
{
	WRITE_REG(MEMIO_REG(TWI_L),DONE(0)|FULL(0)|RECV(inout)|WIDTH_9(width-1)|INDEX_9(INDEX_ROW_9(row)|INDEX_COL_9(col)));
}
void Ro_Adaptive_TWIR9_SetUp(uint8_t inout,uint16_t width,uint8_t row,uint8_t col)
{
	WRITE_REG(MEMIO_REG(TWI_R),DONE(0)|FULL(0)|RECV(inout)|WIDTH_9(width-1)|INDEX_9(INDEX_ROW_9(row)|INDEX_COL_9(col)));//0x4000c00
}
void Ro_Adaptive_MemControlSetup(uint8_t bStart,uint32_t memLeftWay)
{
	if(memLeftWay==MEM_LEFT_IN)
	{
		WRITE_REG(MEMIO_REG(MEMORY_C),\
		RCTL(MEM_ENABLE)|RVALID(MEM_ENABLE)|RHORIZON(MEM_DISABLE)|RIRQE(MEM_ENABLE)|MEM_RDMAE(MEM_ENABLE)|RST(MEM_DISABLE)|RRCS(MEM_ENABLE)|\
		LCTL(MEM_DISABLE)|LVALID(MEM_ENABLE)|LHORIZON(MEM_DISABLE)|LIRQE(MEM_DISABLE)|MEM_LDMAE(MEM_DISABLE)|LST(bStart)|LRCS(MEM_DISABLE));
	}
	else
	{
		WRITE_REG(MEMIO_REG(MEMORY_C),\
		RCTL(MEM_DISABLE)|RVALID(MEM_ENABLE)|RHORIZON(MEM_DISABLE)|RIRQE(MEM_DISABLE)|MEM_RDMAE(MEM_DISABLE)|RST(bStart)|RRCS(MEM_DISABLE)|\
		LCTL(MEM_ENABLE)|LVALID(MEM_ENABLE)|LHORIZON(MEM_DISABLE)|LIRQE(MEM_ENABLE)|MEM_LDMAE(MEM_ENABLE)|LST(MEM_DISABLE)|LRCS(MEM_DISABLE));
	}
}


#endif

