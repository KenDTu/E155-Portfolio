// lab4_starter.c
// Fur Elise, E155 Lab 4
// Author: Ken Tu

#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_FLASH.h"
#include "STM32L432KC_TIM.h"
#include "STM32L432KC_TIM16.h"
#include <math.h>

// Pitch in Hz, duration in ms
const int notes[][2] = {
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{416,	125},
{494,	125},
{523,	250},
{  0,	125},
{330,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{523,	125},
{494,	125},
{440,	250},
{  0,	125},
{494,	125},
{523,	125},
{587,	125},
{659,	375},
{392,	125},
{699,	125},
{659,	125},
{587,	375},
{349,	125},
{659,	125},
{587,	125},
{523,	375},
{330,	125},
{587,	125},
{523,	125},
{494,	250},
{  0,	125},
{330,	125},
{659,	125},
{  0,	250},
{659,	125},
{1319,	125},
{  0,	250},
{623,	125},
{659,	125},
{  0,	250},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{416,	125},
{494,	125},
{523,	250},
{  0,	125},
{330,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{523,	125},
{494,	125},
{440,	500},
{  0,	0}};

// custom song
// frequency map with note
#define NOTE_C4 261.6
#define NOTE_D4 293.7
#define NOTE_E4 329.6
#define NOTE_F4 349.2
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_BB4 446.2
#define NOTE_C5 523.3


const int notes1[][2] = {
{NOTE_C4, 250}, {NOTE_C4, 250}, {NOTE_D4, 500}, {NOTE_C4, 500}, {NOTE_F4, 500}, {NOTE_E4, 1000},
{NOTE_C4, 250}, {NOTE_C4, 250},

{NOTE_D4, 500}, {NOTE_C4, 500}, {NOTE_G4, 500}, {NOTE_F4, 1000},
{NOTE_C4, 250}, {NOTE_C4, 250},
{NOTE_C5, 500}, {NOTE_A4, 500}, {NOTE_F4, 500},

{NOTE_E4, 500}, {NOTE_D4, 500},
{NOTE_BB4, 250}, {NOTE_BB4, 250},
{NOTE_A4, 500}, {NOTE_F4, 500}, {NOTE_G4, 500}, {NOTE_F4, 1500},

{0, 0}

};

int main(void) {

  RCC->APB1ENR1 |= (1 << 4);  // Enable the APB1ENR1 for the TIM6 +
  RCC->APB2ENR  |= (1 << 17); // Enable the APB2ENR2 for TIM16 + 
  RCC->AHB2ENR  |= (1 << 0);  // Enable the AHB2ENR for the GPIOA +

  // Set the PA6 as the output (MODER bits 13 and 12 to 01) +
  GPIO->MODER &= ~(1 << 13);
  GPIO->MODER |= (1 << 12); 

  initTIM(TIM);// Initialize TIM6 +
  initTIM16(TIM16); // Initialize TIM16 + 

  // testing the frequency + 
  //setFreq(100);  
  //while (1) {
  //  updateOutput();
  //}

  // play the notes
  uint32_t i = 0;
  while (notes1[i][1] != 0) { // while the duration is not 0
    int freq = notes1[i][0];
    int ms = notes1[i][1];
    
    if (freq != 0) {
      setFreq(freq); // output the frequency
    } else {
      GPIO->BSRR = (1 << (22)); // reset PA6 to low (0) if the freq is 0
    }

    startDuration(ms); // start the timer and continue and wait for the update flag

    while (!noteOver()) { 
      if (freq != 0) {
        updateOutput(); // Keep toggle the PA6
      }
    }

    GPIO->BSRR = (1 << (22)); // reset PA6 to low (0) after the note is played
    TIM16->SR &= ~(1 << 0); // clear the duration flag and set to 0 ready for the next note
    i++;
  }
}
