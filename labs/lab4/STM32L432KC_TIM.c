// STM32L432KC_TIM.c
// Source code for TIM functions

#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_TIM.h"

void initTIM(TIM_TypeDef * TIMx) {

  TIM->CR1 |= (1 << 0); // Enable counter by setting bit 0 to 1: Counter enabled
  TIM->PSC = 0b1100001101001111;   // Configure prescale register to 49,999 so that using formula count_clk = fck_osc (8MHz)/(PSC[15:0] + 1) = 1600 Hz
  TIM->ARR = 0b1111111111111111;  // Configure auto-reload register (max count) to be maximum value for a 16 bit binary number
  
}

void delay_millis(TIM_TypeDef * TIMx, uint32_t ms) {
  // TODO: Add your function definition
}
