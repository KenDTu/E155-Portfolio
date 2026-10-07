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
  TIM->EGR |= (1 << 0);  // Restart the TIM6 counter // sure? + 
}

// Outputs the desired frequency for the the note
void freqOutput(int freq) {
  
  // TIM->PSC = round((4000000/freq) - 1); // set the PSC from desired frequency for the note on TIM6

  TIM->PSC = 0;
  int centralCLK = 4000000/(TIM->PSC + 1); // actual frequency of our counter
  TIM->ARR = round(2000000/(2*freq) - 1); // works for frequencies above 31Hz. For lower frequencies, increase PSC
  TIM->EGR |= (1 << 0);   // force update so PSC/ARR are loaded


}

// toggle the output signal +
void updateOutput(void) {
  if (TIM->SR & 0x0001) {  // if update event happened for UIF

     TIM->SR &= ~(1 << 0); // clear the flag
     togglePin(6);     // toggle the pin

  }

}
