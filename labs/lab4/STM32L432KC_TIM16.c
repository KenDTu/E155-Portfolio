// STM32L432KC_TIM16.c
// Source code for TIM functions

#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_TIM.h"
#include "STM32L432KC_TIM16.h"
#include <math.h>


// Uses the basic counter on TIM16 +
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

 // Prolongs the duration of the note
void startDuration(int ms) {
  TIM16->CR1 &= ~(1 << 0 ); // stop the counter
  // Making the counter enumerate in 1ms ticks
  TIM16->PSC = 3999;  // using clk = 4000000/1000 - 1 = 3999 (1 ms ticks)
  TIM16->ARR = ms - 1; // make the clock count to the top duration
  TIM16->EGR |= (1 << 0); // force update so PSC/ARR are loaded
  TIM16->SR &= ~(1 << 0); // force clear the UIF max count reach signal
  TIM16->CNT = 0;      // set count back to zero
  TIM16->CR1 |= (1 << 0); // begin counting at the new 1 ms per tick

}

// returns 1 when the note is finished using the UIF marker
int noteOver(void) {
  return TIM16->SR & (1 << 0); // returns the UIF flag
}
