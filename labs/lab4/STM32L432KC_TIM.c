// STM32L432KC_TIM.c
// Source code for TIM functions

#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_TIM.h"
#include <math.h>

// Uses the basic timer on TIM6
void initTIM(TIM_TypeDef * TIMx) {

  TIM->CR1 |= (1 << 0); // Enable counter by setting bit 0 to 1: Counter enabled +
  TIM->CR1 |= (1 << 7); // Enable preload register to transfer contents at each update event, UEV, by setting the ARPE enable bit +
  TIM->CR1 &= ~(1 << 1); // Settinng UDIS bit to 0 to enable the preloading feature from above - this enables UEV +
  TIM->CR1 |= (1 << 11); // Enable the UIF remapping +

  // default settings to be set when we use the TIM->ARR when we calculate the desired freq
  TIM->PSC |= 0;   // Configure prescale register to 0 by default +
  TIM->ARR |= 0xFFFF;  // Configure auto-reload register (max count) to be maximum value for a 16 bit binary number +
  TIM->EGR |= (1 <<0);  // Restart the TIM6 counter // sure? + 
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
