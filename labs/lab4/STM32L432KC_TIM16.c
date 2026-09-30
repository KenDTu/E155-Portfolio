// STM32L432KC_TIM16.c
// Source code for TIM functions

#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_TIM.h"
#include "STM32L432KC_TIM16.h"

void initTIM16(TIM16_TypeDef * TIMx) {
  // TODO: Add your function definitions

  // Disable slave mode
  
  // Configure counter
  //TODO: What goes here?  Configure prescale register
  //TODO: What goes here?  Configure auto-reload register
   // Enable counter by setting bit 0 to 1: Counter enabled
}

void delay_millis16(TIM16_TypeDef * TIMx, uint32_t ms) {
  // TODO: Add your function definition
}