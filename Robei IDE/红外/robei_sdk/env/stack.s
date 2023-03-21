
#define stack size
.equ StackSys,		0x01000000		#0x01020000 ;01020000 0x20020000
.equ StackIrq,		0x01001000		#0x01022000 ;01022000
.equ StackFiq,		0x01002000		#0x01024000 ;01024000
.equ StackAbt,		0x01003000		#0x01026000 ;01026000
.equ StackPAb,		0x01004000		#;01026000
.equ StackUnd,		0x01005000		#0x01028000 ;01028000
.equ StackSvc,		0x01006000		#0x0102a000 ;0102a000

.equ bottom_of_heap,0x01030000 #0x20030000 ;01030000 ;0x01060000
.equ top_of_Stacks,	0x01050000 #0x20050000 ;01050000 ;0x01070000

.equ Cop_Base,		0xfffe4000
.equ Cp15_SCon,		0xfffe4180 #crn[11:8]=1, cp#[7]=1, cop2[6]=0, crm[5:2]=0
.equ Cp15_DAP,		0xfffe4580 #crn[11:8]=5, cp#[7]=1, cop2[6]=0, crm[5:2]=0
.equ Cp15_Area0,	0xfffe4680 #crn[11:8]=6, cp#[7]=1, cop2[6]=0, crm[5:2]=0
.equ Cp15_Area1,	0xfffe4684 #crn[11:8]=6, cp#[7]=1, cop2[6]=0, crm[5:2]=1
.equ Cp15_Area2,	0xfffe4688 #crn[11:8]=6, cp#[7]=1, cop2[6]=0, crm[5:2]=2
.equ Cp15_Area3,	0xfffe468c #crn[11:8]=6, cp#[7]=1, cop2[6]=0, crm[5:2]=3
.equ Cp15_Area4,	0xfffe4690 #crn[11:8]=6, cp#[7]=1, cop2[6]=0, crm[5:2]=4
.equ Cp15_Area5,	0xfffe4694 #crn[11:8]=6, cp#[7]=1, cop2[6]=0, crm[5:2]=5
.equ Cp15_Area6,	0xfffe4698 #crn[11:8]=6, cp#[7]=1, cop2[6]=0, crm[5:2]=6
.equ Cp15_Area7,	0xfffe469c #crn[11:8]=6, cp#[7]=1, cop2[6]=0, crm[5:2]=7

#define protection area            ---
.equ MPU_En,		117447287  #0x07001a77 ;cache, branch, rom, mpu enable  ++
#.equ WB_En,		117447295  #0x07001a7f ;cache, mmu, write-buffer enable ++

.equ Area0,   		0x000006bf #;4G,	base = 0000_0000, read-write, unbufferrable, uncacheable
.equ Area1,   		0x000004a7 #;1M,	base = 0000_0000~000f_ffff, user read-only, unbufferrable, cacheable
.equ Area2,   		0x010007a5 #;512K,	base = 0100_0000~0107_ffff, read-write, bufferrable, cacheable
.equ Area3,   		0x010807a5 #;512K,	base = 0108_0000~0108_ffff, read-write, bufferrable, cacheable
.equ Area4,  		0x100007a5 #;512K,	base = 1000_0000~1007_ffff, read-write, bufferrable, cacheable
.equ Area5,  		0x100807a5 #;512K,	base = 1008_0000~100f_ffff, read-write, unbufferrable, uncacheable
.equ Area6,   		0x65f807a5 #;512K,	base = 65f8_0000~65ff_ffff, read-write, unbufferable, cacheable
.equ Area7,     	0x200007a5 #;512K,	base = 2000_0000~2007_ffff, read-write, bufferrable, cacheable

.equ DPermission, 	0x0000bfff #;a1[3:2] user read-only (10), a0, a2-a6 read-write
.equ IPermission, 	0x0000a000 #;a0-a7 user read-only

#.equ Table_Base  	81920      #0x00014000 ;translation table base
#.equ Domain      	1431655765 #0x55555555

		
#initialize stack
//InitStack:
.macro macro_InitStack

#setup system mode stack
	li		 t1, 0x5f
	csrrw    a0, mie, t1

#;setup cp15 area register
    li	t5, Cp15_Area0
    li	t1, Area0
    sw	t1, 0(t5)

    li	t5, Cp15_Area1
    li	t1, Area1
    sw 	t1, 0(t5) 

    li	t5, Cp15_Area2
    li	t1,  Area2
    sw	t1, 0(t5) 

    li	t5, Cp15_Area3  
    li	t1, Area3 
    sw	t1, 0(t5) 

    li	t5, Cp15_Area4
    li	t1, Area4
    sw	t1, 0(t5) 

    li	t5, Cp15_Area5
    li	t1, Area5
    sw	t1, 0(t5)
    
    li	t5, Cp15_Area6
    li	t1, Area6
    sw	t1, 0(t5)

    li	t5, Cp15_Area7
    li	t1, Area7
    sw	t1, 0(t5)
    
#setup permission register
    li	t5, Cp15_DAP
    li	t1, DPermission
    sw	t1, 0(t5)

#enable cp15 sys control register
	li    t5, Cp15_SCon
	li      t1, MPU_En
	sw    t1, 0(t5)
.endm
   
#/*********************************************************************************************************
#**                            End Of File
#********************************************************************************************************/
