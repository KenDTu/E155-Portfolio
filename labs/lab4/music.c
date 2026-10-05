// music.c
// Source code for music functions

#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_TIM.h"
#include "STM32L432KC_TIM16.h"
#include "music.h"


/**
 * \brief Plays a note for a given frequency and duration
 * \param freq The frequency of the note
 * \param duration The duration of the note in ms
 */

 
 void playNote(int freq, int duration) { 

 uint32_t f_CLK = 4000000; // frequency of internal clock - which by default is 4MHz

  if (freq > 0) {
    TIM16->PSC = 0; // set the PSC to 0 for the maximum timer resolution
    TIM16->ARR = (f_CLK/ freq) - 1; // achieves 'freq' Hz and the 2 because the GPIO must toggle twice (once high, once low)
    TIM16->CCR1 = (TIM16->ARR + 1) / 2; // 50% duty cycle
    TIM16->CNT = 0;  // reset counter register
    TIM16->EGR |= (1 << 0); // Force register shadow update
    TIM16->CR1 |= (1 << 0); // Enable TIM6 PWM output
  } else {
  // rest
    TIM->CR1 &= ~(1 << 0); // Disable the TIM6 during rest
    digitalWrite(SPEAKER_PIN, GPIO_HIGH); 
  }

  delay_millis(TIM, duration);

  // remove PWM at end
  TIM16->CCR1  &= ~(1 << 0);
  TIM16->EGR |= (1 << 0);

  }

