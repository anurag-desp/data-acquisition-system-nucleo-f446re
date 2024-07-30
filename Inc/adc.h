/*
 * adc.h
 *
 *  Created on: Jul 29, 2024
 *      Author: Anurag
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "pll.h"
#include "stm32f446xx.h"
#include "gpio.h"

#define NUM_ADC_PORTS 3
#define TOTAL_NUM_OF_CHANNELS 16
typedef enum {
	ADC_PORT_1 = 0,
	ADC_PORT_2 = 1,
	ADC_PORT_3 = 2,

} ADC_Port_Type;

extern volatile uint32_t ADC1_digital_value;
extern volatile uint32_t ADC2_digital_value;
extern volatile uint32_t ADC3_digital_value;

extern void ADCx_init(ADC_TypeDef* ADCx);
extern  uint8_t check_end_of_conversion_status(ADC_TypeDef* ADCx);
extern  void clear_end_of_conversion_staus(ADC_TypeDef* ADCx);
extern  void enable_interrupt_on_end_of_conversion(ADC_TypeDef* ADCx);
extern  void enable_adc_converter(ADC_TypeDef* ADCx);
extern  void disable_adc_converter(ADC_TypeDef* ADCx);
extern  void set_single_conversion_mode(ADC_TypeDef* ADCx);
extern  void set_continuous_conversion_mode(ADC_TypeDef* ADCx);
extern  void start_conversion(ADC_TypeDef* ADCx);
extern  uint32_t get_data(ADC_TypeDef* ADCx);
extern  void set_regular_sequence(ADC_TypeDef* ADCx, uint8_t num_of_channels, uint8_t channels[]);

#endif /* ADC_H_ */
