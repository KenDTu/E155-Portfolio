// main.c
// Aabhas Senapati
// asenapati@hmc.edu
// 09/10/25
// Code to measure the speed of motors using rotary encoders and interrupts

#include "main.h"
#include <stdio.h>
#include "stm32l432xx.h"

// Function used by printf to send characters to the laptop
int _write(int file, char *ptr, int len) {
    int i = 0;
    for (i = 0; i < len; i++) {
        ITM_SendChar((*ptr++));
    }
    return len;
}

// Global variables for encoder counting
volatile int encoderCount = 0;

void initEncoderInterrupt(void) {

    // 2. Configure EXTICR for PB6 (EXTI6 is in EXTICR2, bits [11:8])
    SYSCFG->EXTICR[1] &= ~(0xF << 8); // Clear EXTI6 configuration
    SYSCFG->EXTICR[1] |= (0x1 << 8);  // Select PB6 (port B = 0x1)
    
    // 3. Configure EXTICR for PB7 (EXTI7 is in EXTICR2, bits [15:12])
    SYSCFG->EXTICR[1] &= ~(0xF << 12); // Clear EXTI7 configuration
    SYSCFG->EXTICR[1] |= (0x1 << 12);  // Select PB7 (port B = 0x1)

    // Configure interrupt for BOTH rising and falling edge of GPIO pin for PB6
    // 1. Configure mask bit
    EXTI->IMR1 |= (1 << 6); // Enable interrupt on EXTI line 6
    
    // 2. Enable rising edge trigger
    EXTI->RTSR1 |= (1 << 6); // Enable rising edge trigger on EXTI6
    
    // 3. Enable falling edge trigger
    EXTI->FTSR1 |= (1 << 6); // Enable falling edge trigger on EXTI6

    // Configure interrupt for BOTH rising and falling edge of GPIO pin for PB7
    // 1. Configure mask bit
    EXTI->IMR1 |= (1 << 7); // Enable interrupt on EXTI line 7
    
    // 2. Enable rising edge trigger
    EXTI->RTSR1 |= (1 << 7); // Enable rising edge trigger on EXTI7
    
    // 3. Enable falling edge trigger
    EXTI->FTSR1 |= (1 << 7); // Enable falling edge trigger on EXTI7
    
    // 4. Turn on EXTI9_5 interrupt in NVIC_ISER (covers both EXTI6 and EXTI7)
    NVIC->ISER[0] |= (1 << EXTI9_5_IRQn);

}


int main(void) {
    // Enable LED_PIN as output to check toggling and latency of interrupts
    gpioEnable(GPIO_PORT_B);
    pinMode(LED_PIN, GPIO_OUTPUT);

    // Enable encoder pins as input and pullup
    pinMode(ENCODER_A_PIN, GPIO_INPUT);
    GPIOB->PUPDR |= _VAL2FLD(GPIO_PUPDR_PUPD6, 0b01); // Set PB6 as pull-up
    
    pinMode(ENCODER_B_PIN, GPIO_INPUT);
    GPIOB->PUPDR |= _VAL2FLD(GPIO_PUPDR_PUPD7, 0b01); // Set PB7 as pull-up

    // Initialize TIM2 for delay functions
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
    initTIM(TIM2);

    // 1. Enable SYSCFG clock domain in RCC
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // Enable interrupts globally
    __enable_irq();

    //Initialize encoder interrupts on both pins and rising and falling edges.
    initEncoderInterrupt();

    printf("Rotary Encoder RPS Monitor\n");
    printf("Pulses Per Revolution: %d\n", PULSES_PER_REV);

    while(1){    

        // Use delay_millis for 1 second timing
        delay_millis(TIM2, 1000);
        //togglePin(LED_PIN);
        // Calculate pulses in the last second
        int pulses = encoderCount;
        encoderCount =0;
        
        // Calculate RPM (use absolute value for display)
        double rps = (((double) pulses)/(4*PULSES_PER_REV));
        
        // Determine direction
        const char* direction;
        if (pulses > 0) {
            direction = "Clockwise";
        } 
        else if (pulses < 0) {
            direction = "Counterclockwise";
            rps = -rps;  // Make RPM positive for display
        } 
        else {
            direction = "Stopped";
        }
        
        // Print results
        printf("Pulses/sec: %d, Direction: %s, RPM: %.2f\n", 
                pulses, direction, rps);
                
    }
    
}

// IRQHandler for EXTI9_5 (both PB6 and PB7 share this handler)
void EXTI9_5_IRQHandler(void){
    digitalWrite(LED_PIN, 1); // toggle to get interrupt latency
    // Check if EXTI6 (PB6 - Channel A) triggered the interrupt
    if (EXTI->PR1 & (1 << 6)){
        // Read Channel A to determine direction
        // When A falls, if B is LOW = Clockwise, if B is HIGH = Counterclockwise
        volatile int channelA = digitalRead(ENCODER_A_PIN);
        volatile int channelB = digitalRead(ENCODER_B_PIN);
        if (channelA  != channelB) {
            // Clockwise rotation - increment counter and toggle LED
            encoderCount++;
        } else {
            // Counterclockwise rotation - decrement counter
            encoderCount--;
        }
        // Clear the interrupt flag (NB: Write 1 to reset)
        EXTI->PR1 |= (1 << 6);
    }
    
    // Check if EXTI7 (PB7 - Channel B) triggered the interrupt
    if (EXTI->PR1 & (1 << 7)){
        // Read Channel B to determine direction
        // When B falls, if A is HIGH = Clockwise, if A is LOW = Counterclockwise
        volatile int channelA = digitalRead(ENCODER_A_PIN);
        volatile int channelB = digitalRead(ENCODER_B_PIN);

        if (channelB  == channelA) {
            // Clockwise rotation - increment counter and toggle LED
            encoderCount++;
        } else {
            // Counterclockwise rotation - decrement counter
            encoderCount--;
        }
       // Clear the interrupt flag (NB: Write 1 to reset)
        EXTI->PR1 |= (1 << 7);
    }
    digitalWrite(LED_PIN, 0); // toggle to get interrupt latency
}