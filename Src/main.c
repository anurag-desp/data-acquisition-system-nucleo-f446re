/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Anurag
 * @brief          : Embedded C Training Final Project
 ******************************************************************************
 */

//#include <stdint.h>
//
//#if !defined(__SOFT_FP__) && defined(__ARM_FP)
//  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
//#endif
//
///*
// *Implement "Data Acquisition System" with the following specifications.
//
//	1. ADC is used to acquire data on request basis.
//	2. UART will be continuously sending the latest data every 1 sec.
//	3. Next data is acquired based on user request and update memory.
//	4. Use LEDs as indicators of operations.
// * */
//
//int main(void)
//{
//    /* Loop forever */
//	for(;;);
//}

#include <stdint.h>
#include "pll.h"
#include "gpio.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif



int main (void) {

	clockSpeed_PLL();
	SysTick_Init();

	GPIOx_init(PB);
	GPIOx_config_mode(PB12, MODER_OUTPUT);
	GPIOx_config_output_speed(PB12, OSPEEDR_HIGH);

	for(;;) {
		GPIOx_set_odr(PB12);
		delay_ms(500);
		GPIOx_reset_odr(PB12);
		delay_ms(500);
	}

	return 0;
}


