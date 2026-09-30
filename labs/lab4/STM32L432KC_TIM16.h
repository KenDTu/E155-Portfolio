// STM32L432KC_TIM16.h
// Header for TIM16 functions

#ifndef STM32L4_TIM16_H
#define STM32L4_TIM16_H

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

#define __IO volatile

// Base addresses
#define TIM16_BASE (0x40014400UL) // base address of TIM16

// TODO: Change the below to the relevant drivers
// PLL
//#define PLLSRC_HSI 0
//#define PLLSRC_HSE 1

//// Clock configuration
//#define SW_HSI  0
//#define SW_HSE  1
//#define SW_PLL  2

/**
  * @brief TIM16
  */

typedef struct
{
  __IO uint32_t CR1;         /*!< TIM16 control register 1,                              Address offset: 0x00 */
  __IO uint32_t CR2;         /*!< TIM16 control register 2,                              Address offset: 0x04 */
  uint32_t      RESERVED0;   /*!< Reserved,                                              Address offset: 0x08 */
  __IO uint32_t DIER;        /*!< TIM16 DMA/interrupt enable register,                   Address offset: 0x0C */
  __IO uint32_t SR;          /*!< TIM16 status register,                                 Address offset: 0x10 */
  __IO uint32_t EGR;         /*!< TIM16 event generation register,                       Address offset: 0x14 */
  __IO uint32_t CMR1;        /*!< TIM16 capture/compare mode register 1,                 Address offset: 0x18 */
  uint32_t      RESERVED1;   /*!< Reserved,                                              Address offset: 0x1C */
  __IO uint32_t CECR;        /*!< TIM16 capture/compare enable register,                 Address offset: 0x20 */
  __IO uint32_t CNT;         /*!< TIM16 counter,                                         Address offset: 0x24 */
  __IO uint32_t PSC;         /*!< TIM16 prescaler,                                       Address offset: 0x28 */
  __IO uint32_t ARR;         /*!< TIM16 auto-reload register,                            Address offset: 0x2C */
  __IO uint32_t RCR;         /*!< TIM16 repetition counter register,                     Address offset: 0x30 */
  __IO uint32_t CCR1;        /*!<TIM16 capture/compare register 1,                       Address offset: 0x34 */
   uint32_t     RESERVED2;   /*!< Reserved,                                              Address offset: 0x38 */
   uint32_t     RESERVED3;   /*!< Reserved,                                              Address offset: 0x3C */
   uint32_t     RESERVED4;   /*!< Reserved,                                              Address offset: 0x40 */
  __IO uint32_t BDTR;        /*!< TIM16 break and dead-time register,                    Address offset: 0x44 */
  __IO uint32_t DCR;         /*!< TIM16 DMA control register,                            Address offset: 0x48 */
  __IO uint32_t DMAR;        /*!< TIM16 DMA address for full transfer,                   Address offset: 0x4C */
  __IO uint32_t OR1;         /*!< TIM16 option register 1,                               Address offset: 0x50 */
  uint32_t      RESERVED5;   /*!< Reserved,                                              Address offset: 0x54 */
  uint32_t      RESERVED6;   /*!< Reserved,                                              Address offset: 0x58 */
  uint32_t      RESERVED7;   /*!< Reserved,                                              Address offset: 0x5C */
  __IO uint32_t OR2;         /*!TIM16 option register 2,                                 Address offset: 0x60 */
   
} TIM16_TypeDef;

#define TIM16 ((TIM16_TypeDef *) TIM16_BASE) // 

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void initTIM16(TIM16_TypeDef * TIMx); 

// void delay_millis16(TIM16_TypeDef * TIMx, uint32_t ms); // TIMER16 does not require a delay

#endif
