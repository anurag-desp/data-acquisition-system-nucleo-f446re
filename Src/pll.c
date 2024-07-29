/*
 * pll.c
 *
 *  Created on: Jul 24, 2024
 *      Author: Anurag
 */
#include "pll.h"


volatile uint32_t ms_counter = 0;
volatile uint32_t millis = 0;

void clockSpeed_PLL(void){

    RCC->CR |= RCC_CR_HSION;
    while (!(RCC->CR & RCC_CR_HSIRDY));

    RCC->PLLCFGR = (PLL_M) | (PLL_N << 6) | (PLL_P << 16) | (PLL_Q << 24);
    RCC->PLLCFGR &=~ RCC_PLLCFGR_PLLSRC;

    RCC->CFGR |= RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE2_DIV2 | RCC_CFGR_PPRE1_DIV4;

    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));

    RCC->APB1ENR |= RCC_APB1ENR_PWREN;

    PWR->CR |= PWR_CR_ODEN;
    while (!(PWR->CSR & PWR_CSR_ODRDY)) ;

    PWR->CR |= PWR_CR_ODSWEN;
    while (!(PWR->CSR & PWR_CSR_ODSWRDY)) ;

    FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_5WS;

    RCC->CFGR &=~ RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);
}


void SysTick_Init(){
    SysTick->VAL = 0;
    SysTick->LOAD = (HCLK_FREQ / 1000)- 1;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_TICKINT_Msk |
                    SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(){
    if (ms_counter) ms_counter--;
    millis++;
}

void delay_ms(uint32_t ms){
    ms_counter = ms;
    while (ms_counter);
}

uint32_t getMillis(){
    return millis;
}
