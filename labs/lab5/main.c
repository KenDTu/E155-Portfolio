// main.c
// Ken Tu
// ktu@g.hmc.edu
// 11/06/2026

#include "main.h"

// Define macros

#define ENCODER_A PA8 // Encoders from the motor -- 15 to 10
#define ENCODER_B PA9  //                         -- 5 to 9
#define PPR 120       // Pulses per revolution from the 25GA-370 DC Motor
#define CPR 4         // Count per revolution

// State machine for direction of motion for motor
volatile uint32_t stateA = 0;
volatile uint32_t stateB = 0;

// Used to verify that the PC passes through the IRQ handler
volatile uint32_t countA = 0;
volatile uint32_t countB = 0;

int count = 0;

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

int main(void) {

    // Configures the system clock for the TIMERs
    configureFlash();
    configureClock();

    // 1. Enable SYSCFG clock domain in RCC
    RCC->APB2ENR |= (1 << 0); // SYSCFGEN
    

    // DO NOT USE INTERNAL PULL UP RESISTORS USE EXTERNAL PULL UPS

    // Enable PA5/ NEW PIN e.g. PA9 as input
    gpioEnable(GPIO_PORT_A);
    pinMode(ENCODER_A, GPIO_INPUT);
    //GPIOA->PUPDR |= _VAL2FLD(GPIO_PUPDR_PUPD10, 0b01); // Sets PA5 with pull-down resistor
    //GPIOA->PUPDR |= (0b01 << 2*gpioPinOffset(ENCODER_A)); // Set PA5

    // Enable PA8 as input
    pinMode(ENCODER_B, GPIO_INPUT);
    //GPIOA->PUPDR |= _VAL2FLD(GPIO_PUPDR_PUPD8, 0b01); // Sets PA8 with pull-down resistor
    //GPIOA->PUPDR |= (0b01 << 2*gpioPinOffset(ENCODER_B)); // Set PA8

    // Initialize timer
    RCC->APB1ENR1 |= (1 << 0); // TIM2EN
    initTIM(DELAY_TIM);

    // 2. Configure EXTICR for the input button interrupt

    // Configure EXTICR for the input interrupt on ENCODER_A 5 so external interrupts are mapped to respective encoder pins
    // SYSCFG->EXTICR[1] &= ~(SYSCFG_EXTICR2_EXTI5); // Turns on EXTI line for PA5
    //SYSCFG->EXTICR[3] &= ~(SYSCFG_EXTICR3_EXTI9); // TODO: CHANGE THIS TO CHANGE PIN e.g. to PA9 which turns on EXTI line for another PA9
    SYSCFG->EXTICR[2] &= ~(1 << 4 | 1 << 5 | 1 << 6); // TODO:from Sadhvi enable external interrupt for pin 9 fr

    // SYSCFG->EXTICR[1] |= _VAL2FLD(SYSCFG_EXTICR2_EXTI5, 0b000);

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

        // Enable interrupts globally
    __enable_irq();

    NVIC_EnableIRQ(EXTI9_5_IRQn);   // Turn on EXTI interrupt for lineEXTI lines 5 to 9.
    // NVIC_EnableIRQ(EXTI15_10_IRQn);

    // Setting priorities manually.
    __NVIC_SetPriority(EXTI9_5_IRQn, 1);
    // __NVIC_SetPriority(EXTI15_10_IRQn, 1);

    delay_millis(DELAY_TIM, 1000);

    while(1){
        
        delay_millis(DELAY_TIM, 1000);
        // printf("%d \n", digitalRead(ENCODER_A));
        //printf("%d: ENCODER_A: %d, countA: %d \n", count, countA, digitalRead(ENCODER_A));
        
        count++;
    }
}

void EXTI9_5_IRQHandler(void) {
  
    printf("%d: countA: %d, ENCODER_A: %d, countB: %d, ENCODER_B %d \n", count, countA, digitalRead(ENCODER_A) , countB , digitalRead(ENCODER_B));
    if (EXTI->PR1 & (1 << gpioPinOffset(ENCODER_A))) {   // PA9 → line 9
        EXTI->PR1 = (1 << gpioPinOffset(ENCODER_A));
        countA++;
    }

    if (EXTI->PR1 & (1 << gpioPinOffset(ENCODER_B))) {   // PA8 → line 8
        EXTI->PR1 = (1 << gpioPinOffset(ENCODER_B));
        countB++;
    }
}
