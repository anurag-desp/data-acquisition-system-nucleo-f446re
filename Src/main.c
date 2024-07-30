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
#include "adc.h"
#include "usart.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


int main (void) {

	clockSpeed_PLL();
	SysTick_Init();

	GPIOx_init(PA);
	GPIOx_init(PB);
	GPIOx_config_mode(PA1, MODER_ANALOG);
	GPIOx_config_mode(PA12, MODER_OUTPUT); // ON when reading data
	GPIOx_config_mode(PA6, MODER_OUTPUT); // ON when writing data
	GPIOx_config_mode(PB12, MODER_OUTPUT); // ON when change detected

	ADCx_init(ADC1);
	enable_adc_converter(ADC1);
	set_single_conversion_mode(ADC1);
	uint8_t channels[] = {1};
	set_regular_sequence(ADC1, 1, channels);

	USART2_quick_default_config();

	volatile uint32_t last_retrieved_data = 0u;

	for(;;) {
		start_conversion(ADC1);

		// reading data
		GPIOx_set_odr(PA12);
		GPIOx_reset_odr(PA6);
		clearScreen();
		printf("%s\t reading... \n", KCYN);
		ADC1_digital_value = get_data(ADC1);

		// change detected
		if (last_retrieved_data != ADC1_digital_value) {
			last_retrieved_data = ADC1_digital_value;
			GPIOx_set_odr(PB12);
		} else {
			GPIOx_reset_odr(PB12);
		}

		// writing data
		GPIOx_reset_odr(PA12);
		GPIOx_set_odr(PA6);
		clearScreen();
		// decide text color
		if ((ADC1_digital_value >= 0) && (ADC1_digital_value < 1000)) {
			printf("%s\t\t%ld\n\r", KGRN, ADC1_digital_value);
		} else if ((ADC1_digital_value >= 1000) && (ADC1_digital_value < 3000)) {
			printf("%s\t\t%ld\n\r", KBLU, ADC1_digital_value);
		} else {
			printf("%s\t\t%ld\n\r", KRED, ADC1_digital_value);
		}

		delay_ms(1000);
	}

	return 0;
}


void tx_send(uint8_t c) {
	USART2->DR = c; // load the data into the data register
	while (!(USART2->SR & (1 << 6)));
}


int __io_putchar(int ch){
 tx_send(ch); // USART2_Transmit function
 for(uint32_t i=0;i<1600000;i++);
 return ch;
}
