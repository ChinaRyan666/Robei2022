OUTPUT_ARCH( "riscv" )/*指定一个特定的输出机器结构，参数为bfd库定义的名字之一，可以使用objdump -f 查看*/

ENTRY( _start )/*ENTRY脚本命令 设置入口点，参数为一个符号名*/

/*MEMORY 命令描述了一个内存块在目标中的位置和大小 flash/ram是链接脚本用来引用内存区域的名字*/
/*属性只能是以下字符组成 R 只读 W 读写 X可执行 A可分配 I已初始化 ！反转其后面的所有属性*/

MEMORY
{
  flash (rxai!w) : ORIGIN = 0x20000000, LENGTH = 4M
  ram (wxa!ri) : ORIGIN = 0x01000000, LENGTH = 16K
}
/*ELF格式的目标文件使用程序头，类似于段，程序头描述程序应当如何加载到内存中，使用objdump -p显示，默认的
的链接器将会创建合适的程序头部。但是，有些情况，需要更加精确的方法来指出程序头，可以使用PHDRS命令达到此命令，
链接器仅在创建ELF输出文件时才会关注PHDRS命令*/
PHDRS
{
  flash PT_LOAD;/*PT_LOAD 可加载头部段*/
  ram_init PT_LOAD;
  ram PT_NULL;
}
	/*PT_NULL 表示未使用的程序头
	PT_LOAD 表示此程序头描述了一个从文件加载的头部段
	PT_DYNAMIC 表示一个可以找到动态链接信息的头部段
	PT_INTERP 表示包含程序解释器的名字的头不断
	PT_NOTE表示一个含有note信息的头部段
	PT_SHLIB 保留
	PT_PHDR表示可以找到程序头的头部段
	*/


SECTIONS  /*SECTIONS命令告诉链接器如何将输入段映射到输出段，以及如何把输出端放入内存中*/
{
  __stack_size = DEFINED(__stack_size) ? __stack_size : 2K;

  .init           :
  {
    KEEP (*(SORT_NONE(.init)))
  } >flash AT>flash :flash
 
 /*AT关键字把一个表达式当作自己的参数。这将指定段的实际加载地址。关键字AT>使用内存区域的名字作为参数*/

  .text           :
  {
    *(.text.unlikely .text.unlikely.*)
    *(.text.startup .text.startup.*)
    *(.text .text.*)
    *(.gnu.linkonce.t.*)
  } >flash AT>flash :flash
  /*存储在flash上，并且直接从Flash中运行，其物理地址和虚拟地址相同，text代码段的物理地址在flash上，虚拟地址也在flash上*/

  .fini           :
  {
    KEEP (*(SORT_NONE(.fini)))
  } >flash AT>flash :flash

  PROVIDE (__etext = .);/*有些情况下，仅当一个符号被引用了却没有在任何链接目标中，才需要为链接脚本定义一个符号*/
  PROVIDE (_etext = .);/*PROVIDE关键字可以定义一个符号*/
  PROVIDE (etext = .);

  .rodata         :
  {
    *(.rdata)
    *(.rodata .rodata.*)
    *(.gnu.linkonce.r.*)
  } >flash AT>flash :flash

  . = ALIGN(4);

  .preinit_array  :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >flash AT>flash :flash

  .init_array     :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
    KEEP (*(.init_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >flash AT>flash :flash

  .fini_array     :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
    KEEP (*(.fini_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .dtors))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >flash AT>flash :flash

  .ctors          :
  {
    /* gcc uses crtbegin.o to find the start of
       the constructors, so we make sure it is
       first.  Because this is a wildcard, it
       doesn't matter if the user does not
       actually link against crtbegin.o; the
       linker won't look for a file to match a
       wildcard.  The wildcard also means that it
       doesn't matter which directory crtbegin.o
       is in.  */
    KEEP (*crtbegin.o(.ctors))
    KEEP (*crtbegin?.o(.ctors))
    /* We don't want to include the .ctor section from
       the crtend.o file until after the sorted ctors.
       The .ctor section from the crtend file contains the
       end of ctors marker and it must be last */
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
  } >flash AT>flash :flash

  .dtors          :
  {
    KEEP (*crtbegin.o(.dtors))
    KEEP (*crtbegin?.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
  } >flash AT>flash :flash

  .lalign         :
  {
    . = ALIGN(4);
    PROVIDE( _data_lma = . );
  } >flash AT>flash :flash

  .dalign         :
  {
    . = ALIGN(4);
    PROVIDE( _data = . );
  } >ram AT>flash :ram_init
  /*可以使用‘>region’把一个段指定到此前设置的内存区域内*/

  .data          :
  {
    *(.data .data.*)
    *(.gnu.linkonce.d.*)
    . = ALIGN(8);
    PROVIDE( __global_pointer$ = . + 0x800 );
    *(.sdata .sdata.*)
    *(.gnu.linkonce.s.*)
    . = ALIGN(8);
    *(.srodata.cst16)
    *(.srodata.cst8)
    *(.srodata.cst4)
    *(.srodata.cst2)
    *(.srodata .srodata.*)
  } >ram AT>flash :ram_init
/*数据存在flash中，而将数据段上传到ram中运行，物理地址在flash空间，虚拟地址在ram上*/
  . = ALIGN(4);
  PROVIDE( _edata = . );
  PROVIDE( edata = . );

  PROVIDE( _fbss = . );
  PROVIDE( __bss_start = . );
  .bss            :
  {
    *(.sbss*)
    *(.gnu.linkonce.sb.*)
    *(.bss .bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(4);
  } >ram AT>ram :ram

  . = ALIGN(8);
  PROVIDE( _end = . );
  PROVIDE( end = . );

  .stack ORIGIN(ram) + LENGTH(ram) - __stack_size :
  {
    PROVIDE( _heap_end = . );
    . = __stack_size;
    PROVIDE( _sp = . );
    __freertos_irq_stack_top = .;
  } >ram AT>ram :ram
}
