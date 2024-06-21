
#include "main.h"
#include "rcc.h"
#include "gpio.h"
#include "utils.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <gpio.hpp>

#define SRAM_BB_BASE 0x22000000
#define SRAM_BASE 0x20000000

#define PERI_BB_BASE 0x42000000
#define PERI_BASE 0x40000000

#define SRAM_BB_ADDRESS_FROM_ABS_ADDRESS(var, bit) (SRAM_BB_BASE + (((var) ^ SRAM_BASE) << 5) + (bit << 2))
#define SRAM_BB_ADDRESS_FROM_VAR(var, bit) (SRAM_BB_BASE + (((uint32_t)&(varz)) ^ SRAM_BASE << 5) + (bit << 2))

#define PERI_BB_ADDRESS_FROM_ABS_ADDRESS(var, bit) (PERI_BB_BASE + (((var) ^ PERI_BASE) << 5) + (bit << 2))

void delay(uint64_t del);

const int data[] = {7,5,6,2,8,6,3,2,1,4,5,8,7};

// int print(const char *fmt, ...){
//     va_list ptr; 
//     va_start(ptr, fmt); 
//     char buff[256];

//     int n = vsprintf(buff, fmt, ptr);
//     if(malloc(24)){
//       n += 5;
//     }
//     va_end(ptr);

//     return n;
// }


GPIO GPIOC(GPIOC_BASE_ADDR);

int main(void) {

configureSystemClock();
    

  GPIOC.setPinMode(13, OUTPUT);


  for(;;)
  {
    GPIOC.togglePin(13);
    delay(0xfffff);
  }
  return 0;
}



void delay(uint64_t del)
{
  while(del)
  {
    asm("nop");
    del--;
  }
}






