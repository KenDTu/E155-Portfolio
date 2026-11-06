// main.c
// Ken Tu
// ktu@g.hmc.edu
// 11/06/2026

#include "main.h"

// Define macros

#define ENCODER_A PA5 // Encoders from the motor
#define ENCODER_B PA8


int main(void) {

    // Enable PA5 as input
    gpioEnable(GPIO_PORT_A);
    pinMode(ENCODER_A, GPIO_INPUT);
    GPIOA->PUPDR |= (0b01 << 2*gpioPinOffset(ENCODER_A)); // Set PA5

    // Enable PA8 as input
    gpioEnable(GPIO_PORT_A);
    pinMode(ENCODER_B, GPIO_INPUT);
    GPIOA->PUPDR |= (0b01 << 2*gpioPinOffset(ENCODER_B)); // Set PA8

    // Initialize timer
    RCC->APB1ENR1 |= (1 << 0); // TIM2EN
    initTIM(DELAY_TIM);

    // 1. Enable SYSCFG clock domain in RCC
    RCC->APB2ENR |= (1 << 0); // SYSCFGEN
    // 2. Configure EXTICR for the input button interrupt
    // EXTI7 is bits 14:12 of EXTICR2 (EXTICR[1] in C). Port A is 0b000, so clearing the field selects PA7.
    SYSCFG->EXTICR[1] &= ~(0b111 << 12);

    // Enable interrupts globally
    __enable_irq();

    // Configure interrupt for falling edge of GPIO pin for button
    EXTI->IMR1 |= (1 << gpioPinOffset(BUTTON_PIN));   // 1. Configure mask bit
    EXTI->RTSR1 &= ~(1 << gpioPinOffset(BUTTON_PIN)); // 2. Disable rising edge trigger
    EXTI->FTSR1 |= (1 << gpioPinOffset(BUTTON_PIN));  // 3. Enable falling edge trigger
    NVIC->ISER[0] |= (1 << 23);                       // 4. Turn on EXTI interrupt in NVIC_ISER (EXTI9_5 is IRQ 23)

    while(1){
        delay_millis(DELAY_TIM, 200);
    }

}

// EXTI lines 5-9 share this handler
void EXTI9_5_IRQHandler(void){
    // Check that the button was what triggered our interrupt
    if (EXTI->PR1 & (1 << gpioPinOffset(BUTTON_PIN))){
        // If so, clear the interrupt (NB: Write 1 to reset.)
        EXTI->PR1 = (1 << gpioPinOffset(BUTTON_PIN));

        // Then toggle the LED
        togglePin(LED_PIN);

    }
}
