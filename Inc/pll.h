/*
 * pll.h
 *
 *  Created on: Jul 24, 2024
 *      Author: anurag
 */

#ifndef PLL_H_
#define PLL_H_
#include "stm32f446xx.h"
#include <stdint.h>

#define PLL_M       8ul
#define PLL_N       180ul
#define PLL_P       0ul
#define PLL_Q       2ul

#define HCLK_FREQ       180000000uL
#define APB1_FREQ       (HCLK_FREQ/4)
#define APB2_FREQ       (HCLK_FREQ/2)

extern void clockSpeed_PLL(void);
extern void SysTick_Init();
extern void SysTick_Handler();
extern void delay_ms(uint32_t ms);
extern uint32_t getMillis();

#endif /* PLL_H_ */
