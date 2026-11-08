// main.c
// Ken Tu
// ktu@g.hmc.edu
// 11/06/2026

#include "main.h"

// Define macros

#define ENCODER_A PA5 // Encoders from the motor -- 15 to 10
#define ENCODER_B PA8  //                         -- 5 to 9
#define PPR 120       // Pulses per revolution from the 25GA-370 DC Motor
#define CPR 4         // Count per revolution

// State machine for direction of motion for motor
volatile uint32_t stateA = 0;
volatile uint32_t stateB = 0;

// Used to verify that the PC passes through the IRQ handler
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

    // Configures the system clock for the TIMERs
    configureFlash();
    configureClock();

    // 1. Enable SYSCFG clock domain in RCC
    RCC->APB2ENR |= (1 << 0); // SYSCFGEN

    // Enable PA5 as input
    gpioEnable(GPIO_PORT_A);
    pinMode(ENCODER_A, GPIO_INPUT);
    encoderPinInit(ENCODER_A); // configuring to set pin with pull-up enabled
    //GPIOA->PUPDR |= _VAL2FLD(GPIO_PUPDR_PUPD10, 0b01); // Sets PA5 with pull-down resistor
    //GPIOA->PUPDR |= (0b01 << 2*gpioPinOffset(ENCODER_A)); // Set PA5

    // Enable PA8 as input
    pinMode(ENCODER_B, GPIO_INPUT);
    encoderPinInit(ENCODER_A); // configuring to set pin with pull-up enabled
    //GPIOA->PUPDR |= _VAL2FLD(GPIO_PUPDR_PUPD8, 0b01); // Sets PA8 with pull-down resistor
    //GPIOA->PUPDR |= (0b01 << 2*gpioPinOffset(ENCODER_B)); // Set PA8

    // Initialize timer
    RCC->APB1ENR1 |= (1 << 0); // TIM2EN
    initTIM(DELAY_TIM);

    // 2. Configure EXTICR for the input button interrupt

    // Configure EXTICR for the input interrupt on ENCODER_A 5 so external interrupts are mapped to respective encoder pins
    SYSCFG->EXTICR[1] &= ~(SYSCFG_EXTICR2_EXTI5);
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

    NVIC_EnableIRQ(EXTI9_5_IRQn);   // Turn on EXTI interrupt for lineEXTI lines 5 to 9.
  
    // Enable interrupts globally
    __enable_irq();

    // ============= Explict section from Quinn can IGNORE FOR THE TIME BEING ===============
    // RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // SYSCFGEN

    //// ENCODER_A Explictly
    //EXTI->IMR1 |= _VAL2FLD(EXTI_IMR1_IM10, 1);
    //EXTI->RTSR1 |= _VAL2FLD(EXTI_RTSR1_RT10, 1);
    //EXTI->FTSR1 |= _VAL2FLD(EXTI_FTSR1_FT10, 1);
    //NVIC->ISER[1] |= (1 << EXTI15_10_IRQn);

     // NVIC_EnableIRQ(EXTI15_10_IRQn); // Turn on EXTI interrupt for lineEXTI lines 10 to 15.

    // Explicting setting the priorities of the interrupts
    //__NVIC_SetPriority(EXTI9_5_IRQn, 2);
    //__NVIC_SetPriority(EXTI15_10_IRQn, 1);
     // NVIC->ISER[1] |= (1 << EXTI9_5_IRQn);

    // ============= END OF Explict section from Quinn can IGNORE FOR THE TIME BEING ===============
    
    int count = 0;
    while(1){
        delay_millis(DELAY_TIM, 200);
        printf("%d: ENCODER_A: %d, countA: %d, countB: %d, ENCODER_B %d \n", count, digitalRead(ENCODER_A), countA, digitalRead(ENCODER_B), countB);
        count++;
    }
}

// ENCODER_B
void EXTI9_5_IRQHandler(void){

    // Check that our ENCODER_A was interrupted properly and clear the interrupt flags
    if (EXTI->PR1 & (1 << gpioPinOffset(ENCODER_A))) {
        // If so, clear the interrupt (NB: Write 1 to reset.)
        EXTI->PR1 = (1 << gpioPinOffset(ENCODER_A));
        countA++;
    }
    
    // Check that our ENCODER_B was interrupted properly and clear the interrupt flags
    if (EXTI->PR1 & (1 << gpioPinOffset(ENCODER_B))) {
        // If so, clear the interrupt (NB: Write 1 to reset.)
        EXTI->PR1 = (1 << gpioPinOffset(ENCODER_B));
        countB++;
    }

}

// ================ ENABLER 15 to 10 EXIT IRQ HANDLER FROM QUINN -- IGNORE ============
//// ENCODER_A
//void EXTI15_10_IRQHandler(void){

//    // TODO: When the interrupt occurs, what do you want to happen?
//    int currentA = digitalRead(ENCODER_A);

//    // printf("%d, %d \n" , currentA, currentB);

//    // Setting up position counter using a TIMER

//    // Check that our encoder was interrupted properly and clear the interrupt flags
//    if (EXTI->PR1 & (1 << gpioPinOffset(ENCODER_A))) {
//        // If so, clear the interrupt (NB: Write 1 to reset.)
//        // EXTI->PR1 |= _VAL2FLD(EXTI_PR1_PIF10, 1);
//        EXTI->PR1 = (1 << gpioPinOffset(ENCODER_A));
//        countA++;
//        printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");

//    }

// ================ END OF ENABLER 15 to 10 EXIT IRQ HANDLER FROM QUINN -- IGNORE ============


