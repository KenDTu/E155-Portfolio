// main.c
// Ken Tu
// ktu@g.hmc.edu
// 11/06/2026

#include "main.h"

// Define macros

#define ENCODER_A PA5 // Encoders from the motor
#define ENCODER_B PA8


// Function used by printf to send characters to the laptop
int _write(int file, char *ptr, int len) {
  int i = 0;
  for (i = 0; i < len; i++) {
    ITM_SendChar((*ptr++));
  }
  return len;
}

volatile uint32_t countA = 0;
volatile uint32_t countB = 0;

void computeMotorSpeed(void) {
  printf("\n join \n");
}

int main(void) {

    // Enable PA5 as input
    gpioEnable(GPIO_PORT_A);
    pinMode(ENCODER_A, GPIO_INPUT);
    GPIOA->PUPDR |= (0b01 << 2*gpioPinOffset(ENCODER_A)); // Set PA5

    // Enable PA8 as input
    gpioEnable(GPIO_PORT_A);
    pinMode(ENCODER_B, GPIO_INPUT);
    GPIOA->PUPDR |= (0b01 << 2*gpioPinOffset(ENCODER_B)); // Set PA8

    // Enable PA10 as input
    gpioEnable(GPIO_PORT_A);
    pinMode(PA10, GPIO_OUTPUT);
    GPIOA->PUPDR |= (0b01 << 2*gpioPinOffset(PA10)); // Set PA8

    // Initialize timer
    RCC->APB1ENR1 |= (1 << 0); // TIM2EN
    initTIM(DELAY_TIM);

    // 1. Enable SYSCFG clock domain in RCC
    RCC->APB2ENR |= (1 << 0); // SYSCFGEN

    // 2. Configure EXTICR for the input button interrupt

    // Configure EXTICR for the input interrupt on ENCODER_A PA5 so external interrupts are mapped to respective encoder pins
    SYSCFG->EXTICR[1] &= ~(SYSCFG_EXTICR2_EXTI5);

    // Configure EXTICR for the input interrupt on ENCODER_B PA8
    SYSCFG->EXTICR[2] &= ~(SYSCFG_EXTICR3_EXTI8);

    // Configure interrupt for falling edge of GPIO pin for ENCODER_A
    EXTI->IMR1 |= (1 << gpioPinOffset(ENCODER_A));   // 1. Configure mask bit
    EXTI->RTSR1 &= ~(1 << gpioPinOffset(ENCODER_A)); // 2. Disable rising edge trigger
    EXTI->FTSR1 |= (1 << gpioPinOffset(ENCODER_A));  // 3. Enable falling edge trigger
    // NVIC_EnableIRQ(EXTI2_IRQn);                      // 4. Turn on EXTI interrupt in NVIC_ISER (EXTI9_5 is IRQ 23)

    // Configure interrupt for falling edge of GPIO pin for ENCODER_B
    EXTI->IMR1 |= (1 << gpioPinOffset(ENCODER_B));   // 1. Configure mask bit
    EXTI->RTSR1 &= ~(1 << gpioPinOffset(ENCODER_B)); // 2. Disable rising edge trigger
    EXTI->FTSR1 |= (1 << gpioPinOffset(ENCODER_B));  // 3. Enable falling edge trigger
    // NVIC_EnableIRQ(EXTI3_IRQn);                      // 4. Turn on EXTI interrupt in NVIC_ISER (EXTI9_5 is IRQ 23) 
    NVIC_EnableIRQ(EXTI9_5_IRQn); // Turn on EXTI interrupt for lineEXTI lines 5 to 9.

    // Enable interrupts globally
    __enable_irq();


    while(1){
        delay_millis(DELAY_TIM, 200);
        printf("%d, %d \n", countA, countB);
        computeMotorSpeed();
    }

}

void EXTI9_5_IRQHandler(void){
    
    // Check that our encoder was interrupted properlyy 
    if (EXTI->PR1 & (1 << gpioPinOffset(ENCODER_A))) {
        // If so, clear the interrupt (NB: Write 1 to reset.)
        EXTI->PR1 = (1 << gpioPinOffset(ENCODER_A));
        countA++;

    }

    if (EXTI->PR1 & (1 << gpioPinOffset(ENCODER_B))) {
        // If so, clear the interrupt (NB: Write 1 to reset.)
        EXTI->PR1 = (1 << gpioPinOffset(ENCODER_B));
        countB++;
    }

}

