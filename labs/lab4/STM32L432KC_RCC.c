// STM32L432KC_RCC.c
// Source code for RCC functions

#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_TIM.h"

void configurePLL(void) {
    // Set clock to 80 MHz
    // Output freq = (src_clk) * (N/M) / R
    // (4 MHz) * (N/M) / R = 80 MHz
    // M: XX, N: XX, R: XX
    // Use MSI as PLLSRC

    // Following the instructions to modify the PLL configuration on 184/1600

    RCC->CR &= ~(1 << 24); // Disable the PLL by setting PLLON to 0


    while ((RCC->CR & (((RCC->CR) << 25) & 1))  != 0)  {
      // wait until PLL is unlocked
    } 
    
    (RCC->PLLCFGR & 0b00) | 0b01;                   // PLL Clock Source = MSI
    (RCC->PLLCFGR & 0xFFFF80FF) | (0b1001000 << 8); // Configure N = 80
    (RCC->PLLCFGR & 0xF9FFFFFF) | (0b01 << 25);     // Configure R = 4
    (RCC->PLLCFGR & 0xFFFFFF8F) | (0b000 << 4);     // Configure M = 1
    RCC->PLLCFGR |= (0b1 << 24);                     // Main PLL PLLCLK output enable

    while (((RCC->CR >> 1) & 1) != 1) {
      // wait until PLL is locked
    }

}

void configureClock(void){
    // Configure and turn on PLL
    configurePLL();

    // Select PLL as clock source
    RCC->CFGR |= (0b11 << 0);
    while(!((RCC->CFGR >> 2) & 0b11));



}
