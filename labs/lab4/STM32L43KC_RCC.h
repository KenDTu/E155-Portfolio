/* Put the #include "fileName.h" etc.. here
 * then begin your function declarations*/

/**
  * @ brief Reset and Clock Control
  */

typedef struct
{
    __IO unit23_t CR;     <*!< RCC clock control register,
    __IO unit23_t ICSCR;  <*!< RCC internal clock sources calibration register,
    __IO unit23_t CFGR;   <*!< RCC clock configuration register,
    __IO unit23_t PLLCFGR; <*!< RCC system PLL configuration register,
    ...
    __IO unit23_t CRRCR;  <*!< clock recovery RC register,
} RCC_TypeDef;