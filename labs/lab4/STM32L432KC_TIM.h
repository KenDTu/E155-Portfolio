// STM32L432KC_TIM.h
// Header for TIM6 functions

#ifndef STM32L4_TIM_H
#define STM32L4_TIM_H

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

#define __IO volatile

// Base addresses
#define TIM6_BASE (0x40001000UL) // base address of TIM6

// TODO: Change the below to the relevant drivers
// PLL
//#define PLLSRC_HSI 0
//#define PLLSRC_HSE 1

//// Clock configuration
//#define SW_HSI  0
//#define SW_HSE  1
//#define SW_PLL  2

/**
  * @brief TIM6
  */

typedef struct
{
  __IO uint32_t CR1;         /*!< TIM control register 1,                       Address offset: 0x00 */
  __IO uint32_t CR2;         /*!< TIM control register 2,                       Address offset: 0x04 */
  uint32_t      RESERVED0;   /*!< Reserved,                                     Address offset: 0x08 */
  __IO uint32_t DIER;        /*!< TIM DMA/Interrupt Enable Register,            Address offset: 0x0C */
  __IO uint32_t SR;          /*!< TIM status register,                          Address offset: 0x10 */
  __IO uint32_t EGR;         /*!< Event generation register,                    Address offset: 0x14 */
  uint32_t      RESERVED1;   /*!< Reserved,                                     Address offset: 0x18 */
  uint32_t      RESERVED2;   /*!< Reserved,                                     Address offset: 0x1C */
  uint32_t      RESERVED3;   /*!< Reserved,                                     Address offset: 0x20 */
  __IO uint32_t CNT;         /*!< TIM counter register,                         Address offset: 0x24 */
  __IO uint32_t PSC;         /*!< TIM prescaler register,                       Address offset: 0x28 */
  __IO uint32_t ARR;         /*!< TIM auto-reload register,                     Address offset: 0x2C */
  
} TIM_TypeDef;

#define TIM ((TIM_TypeDef *) TIM6_BASE) 

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void initTIM(TIM_TypeDef * TIMx); 
void setFreq(int ms);
void updateOutput(void);

#endif