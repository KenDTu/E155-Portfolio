// STM32L432KC_TIM16.c
// Source code for TIM functions

#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_TIM.h"
#include "STM32L432KC_TIM16.h"


// Using the PWM on channel 1
void initTIM16(TIM16_TypeDef * TIMx) {

  //TIM16->CR1 |= (1 << 0); // Enable counter by setting bit 0 to 1: Counter enabled
  //TIM16->PSC |= 0b1100001101001111;   // Configure prescale register to 49,999 so that using formula count_clk = fck_osc (4MHz)/(PSC[15:0] + 1) = 1600 Hz
  //TIM16->ARR |= 0b1111111111111111;  // Configure auto-reload register (max count) to be maximum value for a 16 bit binary number

  TIM16->PSC = 3999;
  TIM16->ARR = 0xFFFF; 
  TIM16->CCR1 = 0;
  TIM16->CCMR1 |= (0b110 << 4) | (1 << 3); // PWM mode 1 OC1M[2:0]
  TIM16->CCER |= (1 << 0); // Bit 0 CC1E capture enable
  TIM16->BDTR |= (1 << 15);   // Main output enable (MOE)
  TIM16->CR1 |= (1 << 7);  // Buffer auto-reload preload enable (ARPE)
  TIM16->EGR |= (1 << 0); // load register by updating event
  TIM16->CR1 |= (1 << 0); // start TIM16 counter

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