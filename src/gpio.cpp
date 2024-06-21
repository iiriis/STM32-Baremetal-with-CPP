
#include "rcc.h"
#include "utils.h"
#include "gpio.hpp"

#define STR(X,Y) X##Y



GPIO::GPIO(uint32_t GPIO_BASE_ADDR)
{
  this->gpio = (gpio_t*)(GPIO_BASE_ADDR);
  RCC_AHB1ENR |= _bit((((GPIO_BASE_ADDR >> 8) & 0xFF) >> 2));
}


void GPIO::setPinMode(uint8_t pin, MODE mode){
  if(pin < 16){
    this->gpio->REG_MODER &= ~(3 << (pin << 1));
    this->gpio->REG_MODER |= ((uint8_t)mode << (pin << 1));
  }
}

void GPIO::togglePin(uint8_t pin)
{
  if(pin < 16){
    this->gpio->REG_ODR ^= (1<<pin);
  }
}

GPIO::~GPIO()
{
}

