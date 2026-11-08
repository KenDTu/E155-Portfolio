// main.h
// Aabhas Senapati
// asenapati@hmc.edu
// 09/10/25
// Header File defining the rotary encoder inputs, pulse per revolution, and the output pin

#ifndef MAIN_H
#define MAIN_H

#include "STM32L432KC.h"
#include <stm32l432xx.h>

///////////////////////////////////////////////////////////////////////////////
// Custom defines
///////////////////////////////////////////////////////////////////////////////
#define LED_PIN PB3
#define ENCODER_A_PIN PB6
#define ENCODER_B_PIN PB7
#define PULSES_PER_REV 408 

#endif // MAIN_H