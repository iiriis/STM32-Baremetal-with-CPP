ENTRY(Reset_Handler);

MEMORY {
  FLASH(rx)  : ORIGIN = 0x08000000, LENGTH = 256k
  SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 64k  /* remaining 64k in a separate address space */
}

_MSP = ORIGIN(SRAM) + LENGTH(SRAM);

_stack_size = 30k;
_heap_size = 20k;

SECTIONS
{
  .isr_vector :
  {
    KEEP(*(.isr_vector))
  } > FLASH

  .text :
  {
    /* this will show individual text sections like text.xx */
    *(.text)
    *(.text*) 
    
    *(.init)
    *(.fini)
  } > FLASH

  .init_array :
  {
    . = ALIGN(4);
    __init_array_start = .;
    KEEP(*(SORT(.init_array*)))
    __init_array_end = .;
    . = ALIGN(4);
  } >FLASH

  .fini_array :
  {
    . = ALIGN(4);
    __fini_array_start = .;
    KEEP(*(.fini_array*))
    __fini_array_end = .;
    . = ALIGN(4);
  } >FLASH

  .rodata :
  {
    *(.rodata*)
  } > FLASH

  .ARM.extab :
  {
    *(.ARM.extab*)
  } > FLASH

  .ARM.exidx :
  {
    . = ALIGN(4);
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
    . = ALIGN(4);
  } > FLASH

  .data : 
  {
    . = ALIGN(4);
    __data_start__ = .;
    *(.data*)
    . = ALIGN(4);
    __data_end__   = .;
  } > SRAM AT> FLASH
  __data_FLASH_start__ = LOADADDR(.data);

  .bss :
  {
    . = ALIGN(4);
    __bss_start__ = .;
    *(.bss*)
    __bss_end__ = .;
    . = ALIGN(4);
  } > SRAM

  .heap :
  {
    _end = .; /* this is provided for the _sbrk to provide end of statically allocated memory so that heap can start */
    end = .;  /* this is provided for the _sbrk to provide end of statically allocated memory so that heap can start */
    . = ALIGN(4);
    _heap_start = .;
    . = . + _heap_size;
    . = ALIGN(4);
  } > SRAM  

  
    /* Remove information from the compiler libraries */
  /* /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  } */
}

ASSERT(((_heap_start + _heap_size) <= (_MSP - _stack_size)), "Heap and Stack may collide !!!");