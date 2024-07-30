/*
 * adc.c
 *
 *  Created on: Jul 28, 2024
 *      Author: Anurag & Aayush
 */


#include "adc.h"


#define ASSERT assert

volatile uint32_t ADC1_digital_value = 0;
volatile uint32_t ADC2_digital_value = 0;
volatile uint32_t ADC3_digital_value = 0;



void ADCx_init(ADC_TypeDef* ADCx) {
	ASSERT((ADCx == ADC1) || (ADCx == ADC2) || (ADCx == ADC3));
	uint8_t index = (ADCx == ADC1)? ADC_PORT_1: (ADCx == ADC2)? ADC_PORT_2: ADC_PORT_3;

	uint32_t ADC_RCC_Enables[] = {
        RCC_APB2ENR_ADC1EN,
        RCC_APB2ENR_ADC2EN,
        RCC_APB2ENR_ADC3EN
	};
	RCC->APB2ENR |= ADC_RCC_Enables[index];
}


uint8_t check_end_of_conversion_status(ADC_TypeDef* ADCx) {
	ASSERT((ADCx == ADC1) || (ADCx == ADC2) || (ADCx == ADC3));

	return (ADCx->SR & ADC_SR_EOC)? 1: 0;
}


void clear_end_of_conversion_staus(ADC_TypeDef* ADCx) {
	ASSERT((ADCx == ADC1) || (ADCx == ADC2) || (ADCx == ADC3));

	ADCx->SR |= ~ADC_SR_EOC;
}


void enable_interrupt_on_end_of_conversion(ADC_TypeDef* ADCx) {
	ASSERT((ADCx == ADC1) || (ADCx == ADC2) || (ADCx == ADC3));

	__disable_irq();
	ADCx->CR1 |= ADC_CR1_EOCIE;
	NVIC_EnableIRQ(ADC_IRQn);
	__enable_irq();
}


void enable_adc_converter(ADC_TypeDef* ADCx) {
	ASSERT((ADCx == ADC1) || (ADCx == ADC2) || (ADCx == ADC3));

	ADCx->CR2 |= ADC_CR2_ADON;
}


void disable_adc_converter(ADC_TypeDef* ADCx) {
	ASSERT((ADCx == ADC1) || (ADCx == ADC2) || (ADCx == ADC3));

	ADCx->CR2 &= ~ADC_CR2_ADON;
}


void set_single_conversion_mode(ADC_TypeDef* ADCx) {
	ASSERT((ADCx == ADC1) || (ADCx == ADC2) || (ADCx == ADC3));

	ADCx->CR2 &= ~ADC_CR2_CONT;
}


void set_continuous_conversion_mode(ADC_TypeDef* ADCx) {
	ASSERT((ADCx == ADC1) || (ADCx == ADC2) || (ADCx == ADC3));

	ADCx->CR2 |= ADC_CR2_CONT;
}


void start_conversion(ADC_TypeDef* ADCx) {
	ASSERT((ADCx == ADC1) || (ADCx == ADC2) || (ADCx == ADC3));

	ADCx->CR2 |= ADC_CR2_SWSTART;
}


uint32_t get_data(ADC_TypeDef* ADCx) {
	ASSERT((ADCx == ADC1) || (ADCx == ADC2) || (ADCx == ADC3));
	while(check_end_of_conversion_status(ADCx) == 0);
	clear_end_of_conversion_staus(ADCx);

	return (ADCx->DR & (0xFFF));
}


void set_regular_sequence(ADC_TypeDef* ADCx, uint8_t num_of_channels, uint8_t channels[]) {
	ASSERT((num_of_channels > 0) && (num_of_channels < TOTAL_NUM_OF_CHANNELS));
	ASSERT((ADCx == ADC1) || (ADCx == ADC2) || (ADCx == ADC3));

	ADCx->SQR1 = 0;
	ADCx->SQR2 = 0;
	ADCx->SQR3 = 0;

	uint8_t channel = 0;
	uint8_t sequence1 = 0,
			sequence2 = 0,
			sequence3 = 0;

	for (uint8_t i = 0; i < num_of_channels; i++) {
		channel = channels[i];
		if ((i >= 0) && (i < 6)) {
			ADCx->SQR3 = (channel << sequence1);
			sequence1 += 5;
		} else if ((i >= 6) && (i < 12)) {
			ADCx->SQR2 = (channel << sequence2);
			sequence2 += 5;
		} else if ((i >= 12) & (i < 16)) {
			ADCx->SQR3 = (channel << sequence2);
			sequence3 += 5;
		}
	}

	ADCx->SQR3 |= (num_of_channels - 1);
}


void ADC_IRQHandler(void) {
	if (check_end_of_conversion_status(ADC1)) {
		clear_end_of_conversion_staus(ADC1);
		ADC1_digital_value = ADC1->DR & (0xFFF);
		return;
	}

	if (check_end_of_conversion_status(ADC2)) {
		clear_end_of_conversion_staus(ADC2);
		ADC2_digital_value = ADC2->DR & (0xFFF);
		return;
	}

	if (check_end_of_conversion_status(ADC3)) {
		clear_end_of_conversion_staus(ADC3);
		ADC3_digital_value = ADC3->DR & (0xFFF);
		return;
	}
}
