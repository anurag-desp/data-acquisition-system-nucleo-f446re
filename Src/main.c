/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Anurag & Aayush
 * @brief          : Embedded C Training Final Project
 ******************************************************************************
 */



/* ********************************************
   *    P R O B L E M    S T A T E M E N T    *
   ********************************************/
/*Implement "Data Acquisition System" with the following specifications.

	1. ADC is used to acquire data on request basis.
	2. UART will be continuously sending the latest data every 1 second.
	3. Next data is acquired based on user request and update memory.
	4. Use LEDs as indicators of operations.
*/


#include <stdint.h>	/* For type definitions*/
#include "pll.h"	/* For system clock and time delays*/
#include "gpio.h"	/* For GPIO pin configurations*/
#include "adc.h"	/* For ADCx configurations*/
#include "usart.h"	/* For USART2 configurations*/

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


int main (void) {

	// initializing PLL and SysTick
	clockSpeed_PLL();
	SysTick_Init();

	/***************************************************
	 * 		G P I O    C O N F I G U R A T I O N S     *
	 ***************************************************/
	GPIOx_init(PA);	/* initializing(Enabling Bus) for GPIOA */
	GPIOx_init(PB);	/* initializing(Enabling Bus) for GPIOB */

	// LIGHT INDICATORS
	GPIOx_config_mode(PA12, MODER_OUTPUT);	/* ON when reading data */
	GPIOx_config_mode(PA6, MODER_OUTPUT);	/* ON when writing data */
	GPIOx_config_mode(PB12, MODER_OUTPUT);	/* ON when change detected */

	// ADC ANALOG INPUT PIN
	GPIOx_config_mode(PA1, MODER_ANALOG);


	/***************************************************
	 * 		A D C 1    C O N F I G U R A T I O N S     *
	 ***************************************************/
	ADCx_init(ADC1);	/* initializing(Enabling Clock) for ADC1 */
	enable_adc_converter(ADC1);	/* Enable ADC */
	set_single_conversion_mode(ADC1);	/* Set ADC to single conversion mode
	 	 	 	 	 	 	 	 	 	   to only read data from the pin when
	 	 	 	 	 	 	 	 	 	   required*/

	uint8_t channels[] = {1};	/* Number of channels to listen from.
								   By default there is only one channel */
	uint8_t num_of_channels_to_read = 1;
	set_regular_sequence(ADC1, num_of_channels_to_read, channels);	/* Setting the sequence of reading
																		from ADC and the number of
																		channels to read from */



	/***************************************************
	 * 	  U S A R T 2    C O N F I G U R A T I O N S   *
	 ***************************************************/
	USART2_quick_default_config();	/* Setting up USART2 with default configurations
									   to transmit data from PA2 and receive data from
									   PA3 */



	volatile uint32_t last_retrieved_data = 0u; /* to keep track of the last read data and blink the
	 	 	 	 	 	 	 	 	 	 	 	   the led at PB12 upon change detection */


	/******************************
	 * 	L O O P    F O R E V E R  *
	 ******************************/
	for(;;) {
		start_conversion(ADC1);	/* Trigger SWSTART bit of ADC_CR2 every time
		 	 	 	 	 	 	   data is to be read */

		// reading data
		GPIOx_set_odr(PA12);	/* turn LED at PA12 ON to indicate reading */
		GPIOx_reset_odr(PA6);	/* turn the writing indicator LED OFF */
		GPIOx_reset_odr(PB12);	/* turn the change detection indicator LED OFF */
		clearScreen();
		printf("%s\t reading... \n", KCYN);
		ADC1_digital_value = get_data(ADC1);

		// change detected
		if (last_retrieved_data != ADC1_digital_value) {
			last_retrieved_data = ADC1_digital_value;
			GPIOx_set_odr(PB12);	/* If a change was detected, turn LED at PB12 ON*/
		} else {
			GPIOx_reset_odr(PB12);	/* If a change was not detected, turn LED at PB12 OFF*/
		}

		// writing data
		GPIOx_set_odr(PA6);	/* turn LED at PA6 ON to indicate writing */
		GPIOx_reset_odr(PA12);	/* turn reading indicator LED OFF */

		clearScreen();	/* Clear serial port terminal emulator(GTKTERM) screen */

		// decide text color
		/*
		 * when data in range
		 * [0, 1000)		-> text color: GREEN
		 * [1000, 3000) 	-> text color: BLUE
		 * [3000, beyond)	-> text color: RED
		 * */
		if ((ADC1_digital_value >= 0) && (ADC1_digital_value < 1000)) {
			printf("%s\t\t%ld\n\r", KGRN, ADC1_digital_value); //
		} else if ((ADC1_digital_value >= 1000) && (ADC1_digital_value < 3000)) {
			printf("%s\t\t%ld\n\r", KBLU, ADC1_digital_value);
		} else {
			printf("%s\t\t%ld\n\r", KRED, ADC1_digital_value);
		}

		delay_ms(1000); /* Delay of 1 second after every read cycle */
	}

	return 0;
}



/* to send char to GTKTERM */
void tx_send(uint8_t c) {
	USART2->DR = c; // load the data into the data register
	while (!(USART2->SR & (1 << 6)));
}

/* to send data to GTKTERM via the printf() statement */
int __io_putchar(int ch){
 tx_send(ch); // USART2_Transmit function
 for(uint32_t i=0;i<1600000;i++);
 return ch;
}
