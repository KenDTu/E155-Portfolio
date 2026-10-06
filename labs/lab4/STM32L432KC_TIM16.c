// STM32L432KC_TIM16.c
// Source code for TIM functions

#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_TIM.h"
#include "STM32L432KC_TIM16.h"


// Using the PWM on channel 1
void initTIM16(TIM16_TypeDef * TIMx) {

  TIM16->CR1 |= (1 << 0);  // Enable the counter +
  TIM16->CR1 &= ~(1 << 1); // Enable the UEV +
  TIM16->CR1 |= (1 << 7);  // Enable the ARPE +
  TIM16->CR1 |= (1 << 11); // Enable the UIF status bit remapping +
  
  // default settings to be set when we use the TIM16->ARR when we calculate the ARR required from the duration
  TIM16->PSC = 0;      // Configure to be zero by default + 
  TIM16->ARR = 0xFFFF; // Configure to be max by default and set in the ARR function in playNote
  TIM16->EGR |= (1 << 0);  // Restart the TIM16 counter // sure? + 

}

 // TIMER16 does not require a delay
void delay_millis16(TIM_TypeDef * TIMx, uint32_t ms) {

  TIM16->PSC = 3999;
  TIM16->ARR = ms - 1;
  TIM16->CNT = 0;

  // force update event
  TIM16->EGR |= (1 << 0);
  TIM16->SR &= ~(1 << 0);

  // start counter
  TIM16->CR1 |= (1 << 0);

  // wait until overflow
  while (!(TIM16->SR & (1 << 0)));

  // clear timer
  TIM16->CR1 &= ~(1 << 0); // disable counter
  TIM16->PSC=0;

}

// Do something with the square wave?