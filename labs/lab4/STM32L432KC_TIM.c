// STM32L432KC_TIM.c
// Source code for TIM functions

#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_TIM.h"

void initTIM(TIM_TypeDef * TIMx) {

  TIM->CR1 |= (1 << 0); // Enable counter by setting bit 0 to 1: Counter enabled
  TIM->CR1 |= (1 << 11); // Enable the UIF remapping
  // (RCC->PLLCFGR & 0xFFFF80FF) | (0b1001000 << 8)
  TIM->PSC |= 399;   // Configure prescale register to 3999 so that using formula count_clk = fck_osc (4MHz)/(PSC[15:0] + 1) = 10KHz
  TIM->ARR |= 0xFFFF;  // Configure auto-reload register (max count) to be maximum value for a 16 bit binary number
  TIM->EGR |= (1 <<0);  // Restart the TIM6 counter
}

void delay_millis(TIM_TypeDef * TIMx, uint32_t ms) {

  if (ms == 0) {
    return;
  }
  
  TIM->CR1 &= ~(1 << 0);  // End of song so STOP
  TIM->ARR = ms - 1;      // Stores the duration (ms) - 1
  TIM->CNT = 0; // TODO: is this incorret?  Reset counter value to 0 
  TIM->EGR |= (1 << 0); // Update generation);
  TIM->SR &= ~(1 << 0);  // Clear the update interrupt flag after the generation
  TIM->CR1 |= (1 << 0);  // Start the TIM6 counter

  while (!(TIM->SR & (1 << 0)));
 // over flow?
 TIM->CR1 &= ~(1 << 0); // Stop

}
