
#include "utils.h"
#include "rcc.hpp"
#include <arm-none-eabi/arm/v5te/softfp/ext/opt_random.h>

void configureSystemClock()
{
  
  RCC_APB1ENR |= 0x10000000;

  volatile rcc_t *RCC = (volatile rcc_t*)(RCC_BASE_ADDR);

  // RCC.PLLCFGR.PLLSRC = 1;
  

  RCC->PLLCFGR.PLLM = 8;   // PLL_CLK = 8
  RCC->PLLCFGR.PLLN = 84;  // VCO = 8*42 = 336
  RCC->PLLCFGR.PLLP = 0;   // PLL_OP = VCO/4 = 84

  RCC->REG_PLLCFGR &=  ~(0x3003F);
  RCC_PLLCFGR &=  ~(0x3003F);

  RCC->CR.PLLON = 1;

  // RCC.REG_PLLCFGR = 

  while (!RCC->CR.PLLON)
  {
  }

  volatile uint8_t z = RCC->CFGR.SWS;

  RCC->CFGR.SW = 2;

  z = RCC->CFGR.SWS;

  RCC->CFGR.SW = 2;


  
  



  // RCC_CR = _setBit(RCC_CR, 16); //Select HSE as main clock
  // while(!_chkBit(RCC_CR, 17));  //wait for HSE to stabilize
  // /*configure PLL*/
  // RCC_PLLCFGR |= _bit(22);      //select HSE as the PLL clock
  // RCC_PLLCFGR |= 25;            //divide the HSE clock with 25 PLLM
  // RCC_PLLCFGR |= (336<<6);      //VCO multiplication factor, PLLN
  // RCC_PLLCFGR &= ~_bit(13);     //clear 13th bit, initially it was set by the reset value; required for the Multiplication factor
  // RCC_PLLCFGR |= (1<<16);       //PLL out div factor 4(PLLP: 01) (336/4 = 84)
  // RCC_PLLCFGR |= (7<<24);       //VCO div factor of 7 for peripherals (336/7=48) , PLLQ

  // RCC_CR |= _bit(24);           //PLL ON
  // while(!_chkBit(RCC_CR, 25));  //wait for PLL to stabilize

  // // RCC_CFGR &= ~_bit(0);
  // RCC_CFGR |= _bit(1);         //Switch clock to PLL
  // while(!((RCC_CFGR & 0b1100) == 0x1000));  //wait until the clock has switched  



}
