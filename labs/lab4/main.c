// lab4_starter.c
// Fur Elise, E155 Lab 4
// Author: Ken Tu

#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_FLASH.h"
#include "STM32L432KC_TIM.h"
#include "STM32L432KC_TIM16.h"
#include "music.h"

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

int main(void) {
  // Using the default clock signal MSI at 4MHz during system reset

  // Configuring use of 80MHz PLL clock
  // configureClock();

  RCC->APB1ENR1 |= (1 << 4);  // Enable the APB1ENR1 for the TIM6
  RCC->APB2ENR  |= (1 << 17); // Enable the APB2ENR2 for TIM16
  // RCC->AHB2ENR  |= (1 << 1);  // Enable the AHB2ENR for the GPIOB

  // Set PB3 as output (MODER bit 7 to 0 and bit 6 to 1
  //GPIO->MODER  |= (1 << 6); // Configure bit 6 to be 1
  //GPIO->MODER  &= ~(1 << 7); // Configure bit 7 to be 0

  // Setting port for the signal out to drive PA6 for GPIOB

  
  RCC->AHB2ENR |= (1 << 0); // GPIOA enable
  GPIO->MODER &= ~(0b11 << 12);
  GPIO->MODER |= (0b10 << 12);    // Set PA6 to alternate function
  GPIO->AFRL &= ~(0xF << 24);
  GPIO->AFRL |= (14 << 24);    // Set AF14 to TIM16 channel 1

  initTIM(TIM);// Initialize TIM6 
  initTIM16(TIM16); // Initialize TIM16

  // Test
  playNote(440, 2000);
  
  // Play the music
  uint32_t i = 0;
  while (notes[i][1] != 0) {   // End the song when duration reads 0
    playNote(notes[i][0], notes[i][1]);
    i++;
  }

  while (1) {
  } 
  
}