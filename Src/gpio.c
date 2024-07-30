/*
 * gpio.c
 *
 *  Created on: Jul 28, 2024
 *      Author: Anurag
 */


#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "pll.h"
#include "stm32f446xx.h"
#include "gpio.h"

#define ASSERT assert
// used to check if the port being accessed has been initialized or
// in other words, if the bus for the port as been enabled.
// initially none of the ports are initialized
//static uint8_t initialized[] = {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};

static GPIO_TypeDef* get_GPIOx_PORT(uint8_t GPIOx) {
	ASSERT((GPIOx >= 0u) && (GPIOx < NUM_PORTS));

	GPIO_TypeDef* GPIOx_PORTS[] = {
			GPIOA,
			GPIOB,
			GPIOC,
			GPIOD,
			GPIOE,
			GPIOF,
			GPIOG,
			GPIOH,
	};

	return GPIOx_PORTS[GPIOx];
}

static inline uint8_t get_port_number(uint8_t pin) {
	ASSERT((pin >= 0U) && (pin < TOTAL_PINS));
	return (pin / NUM_PINS_PER_PORT);
}

static inline uint8_t get_pin_number(uint8_t pin) {
	ASSERT((pin >= 0U) && (pin < TOTAL_PINS));
	return (pin % NUM_PINS_PER_PORT);
}

static uint8_t is_moder_in_af_moder(GPIO_TypeDef* GPIOx, uint8_t pin_number) {
	uint32_t comparator = GPIOx->MODER | (3 << (pin_number * 2));
	comparator &= ~(1 << (pin_number * 2));

	return (GPIOx->MODER ^ comparator) == 0? 1: 0;
}





void GPIOx_init(uint8_t GPIOx) {
	ASSERT((GPIOx >= 0u) && (GPIOx < NUM_PORTS));

	uint32_t GPIO_RCC_Enables[] = {
			RCC_AHB1ENR_GPIOAEN,
			RCC_AHB1ENR_GPIOBEN,
			RCC_AHB1ENR_GPIOCEN,
			RCC_AHB1ENR_GPIODEN,
			RCC_AHB1ENR_GPIOEEN,
			RCC_AHB1ENR_GPIOFEN,
			RCC_AHB1ENR_GPIOGEN,
			RCC_AHB1ENR_GPIOHEN,
	};

	RCC->AHB1ENR |= GPIO_RCC_Enables[GPIOx];
}


void GPIOx_config_mode(uint8_t pin, uint8_t mode) {
	ASSERT((mode >= 0) && (mode < 4));

	uint8_t port = get_port_number(pin);
	uint32_t pin_number = get_pin_number(pin);
	GPIO_TypeDef* GPIOx = get_GPIOx_PORT(port);

	ASSERT((pin == PA5) && (mode != MODER_INPUT));
	ASSERT((pin == PC13) && (mode != MODER_OUTPUT));

	GPIOx->MODER &= ~(3 << (pin_number * 2)); // clearning bits before setting them

	if (mode != MODER_INPUT) {
		GPIOx->MODER |= ((mode) << (pin_number * 2));
	}
}


void GPIOx_config_output_type(uint8_t pin, uint8_t out_type) {
	ASSERT((out_type >= 0) && (out_type < 2));

	uint8_t port = get_port_number(pin);
	uint32_t pin_number = get_pin_number(pin);
	GPIO_TypeDef* GPIOx = get_GPIOx_PORT(port);

	if (out_type == OTYPER_PUSH_PULL) {
		GPIOx->OTYPER &= ~(1 << pin_number);
	} else {
		GPIOx->OTYPER |= (1 << pin_number);
	}
}


void GPIOx_config_output_speed(uint8_t pin, uint8_t out_speed) {
	ASSERT((out_speed >= 0) && (out_speed < 4));

	uint8_t port = get_port_number(pin);
	uint32_t pin_number = get_pin_number(pin);
	GPIO_TypeDef* GPIOx = get_GPIOx_PORT(port);

	GPIOx->OSPEEDR &= ~(3 << (pin_number * 2)); // clearning bits before setting them

	if (out_speed != OSPEEDR_LOW) {
		GPIOx->OSPEEDR |= ((out_speed) << (pin_number * 2));
	}
}


void GPIOx_config_pupd(uint8_t pin, uint8_t pupd) {
		ASSERT((pupd >= 0) && (pupd < 4));

		uint8_t port = get_port_number(pin);
		uint32_t pin_number = get_pin_number(pin);
		GPIO_TypeDef* GPIOx = get_GPIOx_PORT(port);

		GPIOx->PUPDR &= ~(3 << (pin_number * 2)); // clearning bits before setting them

		if (pupd != PUPDR_NO_PU_PD) {
			GPIOx->PUPDR |= ((pupd) << (pin_number * 2));
		}
}


void GPIOx_config_alternate_function(uint8_t pin, uint8_t alternate_function) {
	ASSERT((alternate_function >= 0) && (alternate_function < 16));

	uint8_t port = get_port_number(pin);
	uint8_t pin_number = get_pin_number(pin);
	GPIO_TypeDef* GPIOx = get_GPIOx_PORT(port);

	ASSERT(is_moder_in_af_moder(GPIOx, pin_number));

	uint8_t af_index = (pin_number < 8)? 0: 1;
	GPIOx->AFR[af_index] &= ~(0xF << (pin_number * 4));
	if (alternate_function > 0) {
		GPIOx->AFR[af_index] |= (alternate_function << (pin_number * 4));
	}
}


void GPIOx_set_odr(uint8_t pin) {
	uint8_t port = get_port_number(pin);
	uint8_t pin_number = get_pin_number(pin);
	GPIO_TypeDef* GPIOx = get_GPIOx_PORT(port);

	GPIOx->ODR |= (1 << pin_number);
}


void GPIOx_reset_odr(uint8_t pin) {
	uint8_t port = get_port_number(pin);
	uint8_t pin_number = get_pin_number(pin);
	GPIO_TypeDef* GPIOx = get_GPIOx_PORT(port);

	GPIOx->ODR &= ~(1 << pin_number);
}


uint8_t GPIOx_get_idr(uint8_t pin) {
	uint8_t port = get_port_number(pin);
	uint8_t pin_number = get_pin_number(pin);
	GPIO_TypeDef* GPIOx = get_GPIOx_PORT(port);

	return ((GPIOx->IDR & (1 << pin_number)) == 0)? (uint8_t)0: (uint8_t)1;
}
