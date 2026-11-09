// main.c
// Ken Tu
// ktu@g.hmc.edu
// 11/06/2026

#include "main.h"
#include "STM32L432KC_TIM16.h"

// Define macros

#define ENCODER_A PA8 // Encoders from the motor -- 15 to 10
#define ENCODER_B PA9  //                         -- 5 to 9
#define PPR 120       // Pulses per revolution from the 25GA-370 DC Motor
#define CPR 4         // Count per revolution

// State machine for direction of motion for motor
volatile uint32_t stateA = 0;
volatile uint32_t stateB = 0;

volatile uint32_t newA = 0;
volatile uint32_t newB = 0;

// Used to verify that the PC passes through the IRQ handler
volatile uint32_t countA = 0;
volatile uint32_t countB = 0;

// Used to indicate CW or CCW with default CW = 1
volatile int direction = 1;

// With an interrupt to measure 1 second of time for the pulse/s the s value
volatile int totalCount = 0;

// Used to show the line number on the terminal
volatile int count = 0;

// Used velocity for motor
volatile float velocity = 0;

// Used to calculate number of peaks on quad encoder
volatile float positionCount = 0;

volatile int32_t timer = 500;

// Function used by printf to send characters to the laptop
int _write(int file, char *ptr, int len) {
  int i = 0;
  for (i = 0; i < len; i++) {
    ITM_SendChar((*ptr++));
  }
  return len;
}

void configureSystemClocks(void) {
    // Configures the system clock for the TIMERs
    configureFlash();
    // configureClock();
    // select 4HMz as the clock for TIM2

    // 1. Enable SYSCFG clock domain in RCC
    // RCC->APB1ENR1 |= (1 << 0); // SYSCFGEN
    // RCC->APB1ENR1 |= (1 << 0); // TIM2EN
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN; // TIM2

}
void setupInterrupt(void) {
    gpioEnable(GPIO_PORT_A);
    pinMode(ENCODER_A, GPIO_INPUT);
    //GPIOA->PUPDR |= _VAL2FLD(GPIO_PUPDR_PUPD10, 0b01); // Sets PA5 with pull-down resistor
    //GPIOA->PUPDR |= (0b01 << 2*gpioPinOffset(ENCODER_A)); // Set PA5

    // Enable PA8 as input
    pinMode(ENCODER_B, GPIO_INPUT);
    //GPIOA->PUPDR |= _VAL2FLD(GPIO_PUPDR_PUPD8, 0b01); // Sets PA8 with pull-down resistor
    //GPIOA->PUPDR |= (0b01 << 2*gpioPinOffset(ENCODER_B)); // Set PA8


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

    __NVIC_EnableIRQ(EXTI9_5_IRQn);         // Turn on EXTI interrupt for lineEXTI lines 5 to 9.
    // __NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn); // 

    // Setting priorities manually.
    __NVIC_SetPriority(EXTI9_5_IRQn, 1);
    // __NVIC_SetPriority(TIM1_UP_TIM16_IRQn, 2);

    
}

void setupTimer(void) {
    // ============== TIMER SETUP ===================
    //initTIM16(DELAY_TIM);
    initTIM(TIM2); // TIM2
    // RCC->APB1ENR1 |= (1 << 0); // TIM2EN
    // RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN; // TIM2
    // RCC->APB2ENR |= RCC_APB2ENR_TIM16EN; // TIM16

    
    // With an interrupt to measure 1 second of time for the pulse/s the s value
    //TIM16->DIER |= (1 << 6); // Trigger interrupt enable
    //TIM16->DIER |= (1 << 0); // Update interrupt enable
    //TIM16->SR &= ~(1 << 0); // Resets the interrupt flag


}

int main(void) {

    configureSystemClocks();
    setupInterrupt();
    setupTimer();

    delay_millis(TIM2, 1000);
    delay_millis(TIM2, 1000);
    delay_millis(TIM2, 1000);
    delay_millis(TIM2, 1000);
    delay_millis(TIM2, 1000);


    delay_millis(TIM2, 1000);
    delay_millis(TIM2, 1000);
    delay_millis(TIM2, 1000);
    delay_millis(TIM2, 1000);
    delay_millis(TIM2, 1000);

    while(1){

        delay_millis(TIM2, timer); // 2Hz delay
        float d = positionCount;
        positionCount = 0;
        printf("%f, %f \n", positionCount, d);
        // printf("d: %f, positionCount: %f -- %d: Velocity (Includes Direction): %f %d: countA: %d, ENCODER_A: %d, countB: %d, ENCODER_B %d \n", d, positionCount, count, velocity, direction, countA, digitalRead(ENCODER_A) , countB , digitalRead(ENCODER_B));
        velocity = (float)(d * (1000/timer)) / (4 * PPR);
        
        //printf("%d: %f \n", count, velocity);
        //// printf(": Velocity (Includes Direction): %f %d: countA: %d, ENCODER_A: %d, countB: %d, ENCODER_B %d \n", velocity*direction, countA, digitalRead(ENCODER_A) , countB , digitalRead(ENCODER_B));
        //// printf("%d \n", digitalRead(ENCODER_A));
        ////printf("%d: ENCODER_A: %d, countA: %d \n", count, countA, digitalRead(ENCODER_A));
        //count++;
        
        //if (TIM16->SR & ~(1 << 0)) {
        //  positionCount = 0;
        //}
    }
}

void EXTI9_5_IRQHandler(void) {

    // Finding the direction clockwise or counter-clockwise for the motor
    newA = digitalRead(ENCODER_A);
    newB = digitalRead(ENCODER_B); 
  
    if (EXTI->PR1 & (1 << gpioPinOffset(ENCODER_A))) {   // PA9 → line 9
        EXTI->PR1 = (1 << gpioPinOffset(ENCODER_A));
        if (newA == 1 && newB == 1) {
          direction = -1;
        } else if (newA == 0 && newB == 0) {
          direction = -1;
        } else if (newA == 1 && newB == 0) {
          direction = 1;
        } else if (newA == 0 && newB == 1) {
          direction = 1;
        } 
        countA++;
        positionCount+=direction;
    }


    if (EXTI->PR1 & (1 << gpioPinOffset(ENCODER_B))) {   // PA8 → line 8
        EXTI->PR1 = (1 << gpioPinOffset(ENCODER_B));
        if (newA == 1 && newB == 1) {
          direction = 1;
        } else if (newA == 0 && newB == 0) {
          direction = 1;
        } else if (newA == 1 && newB == 0) {
          direction = -1;
        } else if (newA == 0 && newB == 1) {
          direction = -1;
        }
        countB++;
        positionCount+=direction;
    }

    
    count++;
}

void TIM1_UP_TIM16_IRQHandler(void) {
  if (TIM2->SR & (1 << 0)) {
    TIM2->SR &= ~(1 << 0); // Resets the interrupt flag
    printf("test");
    // velocity = (float)positionCount / (4 * PPR);
    // printf(": Velocity (Includes Direction): %f %d: countA: %d, ENCODER_A: %d, countB: %d, ENCODER_B %d \n", velocity, direction, countA, digitalRead(ENCODER_A) , countB , digitalRead(ENCODER_B));
    TIM2->CNT = 0;
  }


}

