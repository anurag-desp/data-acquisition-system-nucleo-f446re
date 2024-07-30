/**
 * @file adc.h
 * @brief Header file for ADC (Analog-to-Digital Converter) operations
 *
 * This file contains declarations for ADC initialization, configuration,
 * and data acquisition functions for STM32F446xx microcontrollers.
 *
 * @author Anurag and Aayush
 * @date Jul 29, 2024
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "pll.h"
#include "stm32f446xx.h"
#include "gpio.h"

#define NUM_ADC_PORTS 3         /**< Number of ADC ports available */
#define TOTAL_NUM_OF_CHANNELS 16 /**< Total number of ADC channels */

/**
 * @brief Enumeration of ADC ports
 */
typedef enum {
    ADC_PORT_1 = 0, /**< ADC Port 1 */
    ADC_PORT_2 = 1, /**< ADC Port 2 */
    ADC_PORT_3 = 2, /**< ADC Port 3 */
} ADC_Port_Type;

/** @brief Digital value from ADC1 */
extern volatile uint32_t ADC1_digital_value;

/** @brief Digital value from ADC2 */
extern volatile uint32_t ADC2_digital_value;

/** @brief Digital value from ADC3 */
extern volatile uint32_t ADC3_digital_value;

/**
 * @brief Initialize the specified ADC
 * @param ADCx Pointer to ADC peripheral to be initialized
 */
extern void ADCx_init(ADC_TypeDef* ADCx);

/**
 * @brief Check the end of conversion status for the specified ADC
 * @param ADCx Pointer to ADC peripheral to check
 * @return End of conversion status (1 if conversion complete, 0 otherwise)
 */
extern uint8_t check_end_of_conversion_status(ADC_TypeDef* ADCx);

/**
 * @brief Clear the end of conversion status for the specified ADC
 * @param ADCx Pointer to ADC peripheral to clear
 */
extern void clear_end_of_conversion_staus(ADC_TypeDef* ADCx);

/**
 * @brief Enable interrupt on end of conversion for the specified ADC
 * @param ADCx Pointer to ADC peripheral to configure
 */
extern void enable_interrupt_on_end_of_conversion(ADC_TypeDef* ADCx);

/**
 * @brief Enable the specified ADC converter
 * @param ADCx Pointer to ADC peripheral to enable
 */
extern void enable_adc_converter(ADC_TypeDef* ADCx);

/**
 * @brief Disable the specified ADC converter
 * @param ADCx Pointer to ADC peripheral to disable
 */
extern void disable_adc_converter(ADC_TypeDef* ADCx);

/**
 * @brief Set single conversion mode for the specified ADC
 * @param ADCx Pointer to ADC peripheral to configure
 */
extern void set_single_conversion_mode(ADC_TypeDef* ADCx);

/**
 * @brief Set continuous conversion mode for the specified ADC
 * @param ADCx Pointer to ADC peripheral to configure
 */
extern void set_continuous_conversion_mode(ADC_TypeDef* ADCx);

/**
 * @brief Start conversion for the specified ADC
 * @param ADCx Pointer to ADC peripheral to start conversion
 */
extern void start_conversion(ADC_TypeDef* ADCx);

/**
 * @brief Get data from the specified ADC
 * @param ADCx Pointer to ADC peripheral to read data from
 * @return The converted digital value
 */
extern uint32_t get_data(ADC_TypeDef* ADCx);

/**
 * @brief Set regular sequence for the specified ADC
 * @param ADCx Pointer to ADC peripheral to configure
 * @param num_of_channels Number of channels in the sequence
 * @param channels Array of channel numbers to be sequenced
 */
extern void set_regular_sequence(ADC_TypeDef* ADCx, uint8_t num_of_channels, uint8_t channels[]);

#endif /* ADC_H_ */