
#include <main.h>
#include <string.h>
#include <__startup.h>




extern uint32_t _MSP;  // Defined in link.ld
__attribute__((section(".isr_vector"))) volatile const uint32_t vector_table [97] = {
    (uint32_t)&_MSP,
    (uint32_t)&Reset_Handler,
    (uint32_t)&NMI_Handler,
    (uint32_t)&NMI_Handler,
    (uint32_t)&HardFault_Handler,
    (uint32_t)&MemoryManagementFault_Handler,
    (uint32_t)&BusFault_Handler,
    (uint32_t)&UsageFault_Handler,
};

void Reset_Handler(void) {

    extern uint8_t __data_start__, __data_end__, __data_FLASH_start__, __bss_start__, __bss_end__;
    // uint8_t *__data_start__ptr = &__data_start__;
    // uint8_t *__data_end__ptr = &__data_end__;
    // uint8_t *__data_FLASH_start__ptr = &__data_FLASH_start__;
    // uint8_t *__bss_start__ptr = &__bss_start__;
    // uint8_t *__bss_end__ptr = &__bss_end__;

    
    memcpy(&__data_start__, &__data_FLASH_start__, (uint32_t)(&__data_end__ - &__data_start__));
    memset(&__bss_start__, 0, (uint32_t)(&__bss_end__ - &__bss_start__));

    _init_array();

    enableFPU();
    (*(volatile uint32_t*)0xE000ED08) = (uint32_t)vector_table;

    main();
    for(;;);
}


void _init_array(){

  extern uint32_t __init_array_start, __init_array_end;

  /* create a function pointer for the init_array vectors */
  typedef void (*init_func_ptr)(void);

  /**  
   *  The init array contains list of vectors for the constructors, make a pointer 
   *  to the starting of the vector list. Grab the value from the vector list as 
   *  the address of the function to jump. And Jump by calling the fuction;
  */
  for(volatile uint32_t *vectors = &__init_array_start; vectors < &__init_array_end; vectors++)
    ((init_func_ptr)(*vectors))();

}


void Default_Handler(void)
{
  while(1);
}
