// main.c
// Ken Tu
// ktu@g.hmc.edu
// 11/06/2026

#include "main.h"

// Define macros

#define ENCODER_A PA6 // Encoders from the motor
#define ENCODER_B PA8
#define PPR 120       // Pulses per revolution from the 25GA-370 DC Motor
#define CPR 4         // Count per revolution

// State machine for direction of motion for motor
volatile uint32_t stateA = 0;
volatile uint32_t stateB = 0;

// 
volatile uint32_t countA = 0;
volatile uint32_t countB = 0;


// Function used by printf to send characters to the laptop
int _write(int file, char *ptr, int len) {
  int i = 0;
  for (i = 0; i < len; i++) {
    ITM_SendChar((*ptr++));
  }
  return len;
}


void computeMotorSpeed(void) {
  printf("\n join \n");
}


// Configure a GPIOA pin as an input with the internal pull-up enabled
static void encoderPinInit(int pin) {
    uint32_t n = gpioPinOffset(pin);
    GPIOA->MODER &= ~(0x3u << (2 * n));   // MODER = 00: input
    GPIOA->PUPDR &= ~(0x3u << (2 * n));   // clear first, so |= can't leave stale bits
    GPIOA->PUPDR |=  (0x1u << (2 * n));   // PUPDR = 01: pull-up
}

int main(void) {

    // Enable PA5 as input
    gpioEnable(GPIO_PORT_A);
    pinMode(ENCODER_A, GPIO_INPUT);
    GPIOA->PUPDR |= (0b01 << 2*gpioPinOffset(ENCODER_A)); // Set PA5

    // Enable PA8 as input
    pinMode(ENCODER_B, GPIO_INPUT);
    GPIOA->PUPDR |= (0b01 << 2*gpioPinOffset(ENCODER_B)); // Set PA8

    // Initialize timer
    RCC->APB1ENR1 |= (1 << 0); // TIM2EN
    initTIM(DELAY_TIM);

    // 1. Enable SYSCFG clock domain in RCC
    RCC->APB2ENR |= (1 << 0); // SYSCFGEN

    // 2. Configure EXTICR for the input button interrupt

    // Configure EXTICR for the input interrupt on ENCODER_A PA6 so external interrupts are mapped to respective encoder pins
    SYSCFG->EXTICR[1] &= ~(SYSCFG_EXTICR2_EXTI6);

    // Configure EXTICR for the input interrupt on ENCODER_B PA8
    SYSCFG->EXTICR[2] &= ~(SYSCFG_EXTICR3_EXTI8);

    // Configure interrupt for falling and rising edge of GPIO pin for ENCODER_A
    EXTI->IMR1 |= (1 << gpioPinOffset(ENCODER_A));   // 1. Configure mask bit
    EXTI->RTSR1 |= (1 << gpioPinOffset(ENCODER_A));  // 2. Enable rising edge trigger
    EXTI->FTSR1 |= (1 << gpioPinOffset(ENCODER_A));  // 3. Enable falling edge trigger

    // Configure interrupt for falling and rising edge of GPIO pin for ENCODER_B
    EXTI->IMR1 |= (1 << gpioPinOffset(ENCODER_B));   // 1. Configure mask bit
    EXTI->RTSR1 |= (1 << gpioPinOffset(ENCODER_B));  // 2. Enable rising edge trigger
    EXTI->FTSR1 |= (1 << gpioPinOffset(ENCODER_B));  // 3. Enable falling edge trigger

    NVIC_EnableIRQ(EXTI9_5_IRQn); // Turn on EXTI interrupt for lineEXTI lines 5 to 9.

    // Enable interrupts globally
    __enable_irq();
    
    int count = 0;
    while(1){
        delay_millis(DELAY_TIM, 200);
        // printf("%d, %d \n", countA, countB);
        printf("%d", count);
        printf(": ENCODER_A: %d, ENCODER_B %d \n", digitalRead(ENCODER_A), digitalRead(ENCODER_B));
        count++;
    }

}

void EXTI9_5_IRQHandler(void){

    // TODO: When the interrupt occurs, what do you want to happen?
    int currentA = digitalRead(ENCODER_A);
    int currentB = digitalRead(ENCODER_B);

    // printf("%d, %d \n" , currentA, currentB);

    // Setting up position counter using a TIMER


    // Check that our encoder was interrupted properly and clear the interrupt flags
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

