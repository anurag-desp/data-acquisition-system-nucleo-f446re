/*
 * usart.c
 *
 * Created on: Jul 30, 2024
 * Author: i3ye
 *
 * This file contains the implementation of UART2 configuration and communication
 * functions for an STM32 microcontroller.
 */

#include "usart.h"


void UART2_init(void) {
    // Enable USART2 clock
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    GPIOx_init(PA);
    GPIOx_config_mode(PA2, MODER_AF);
    GPIOx_config_mode(PA3, MODER_AF);
    GPIOx_config_output_speed(PA2, OSPEEDR_HIGH);
    GPIOx_config_output_speed(PA3, OSPEEDR_HIGH);
    GPIOx_config_alternate_function(PA2, AF7);
    GPIOx_config_alternate_function(PA3, AF7);

    // Configure UART2
    USART2->CR1 = 0x00; // Reset the control register
    USART2->CR1 |= USART_CR1_UE; // Enable UART
    USART2->CR1 &= ~USART_CR1_M; // Set to 8 data bits
    USART2->BRR = (7 << 0) | (24 << 4); // Set baud rate to 115200 (assuming PCLK1 at 45MHz)
    USART2->CR1 |= (1 << 2); // Enable receiver
    USART2->CR1 |= (1 << 3); // Enable transmitter
}


void USART2_clear_CR1(void) {
    USART2->CR1 = 0x00;
}


void USART2_enable(void) {
    USART2->CR1 |= USART_CR1_UE;
}


void USART2_set_word_length(uint8_t length) {
	if (length != USART2_CR1_M_WORD_LENGTH_9)
		USART2->CR1 &= ~USART_CR1_M;
	else
		USART2->CR1 |=  USART_CR1_M;
}


void USART2_enable_transmitter(void) {
    USART2->CR1 |= (1 << PA2);
}


void USART2_enable_receiver(void) {
    USART2->CR1 |= (1 << PA3);
}


void USART2_set_default_baud_rate(void) {
    USART2->BRR = (7 << 0) | (24 << 4);
}


/**
 * @brief Configures UART2 for communication
 *
 * This function sets up UART2 with the following configuration:
 * - Baud rate: 115200
 * - Data bits: 8
 * - Stop bits: 1
 * - Parity: None
 * - Flow control: None
 */
void USART2_quick_default_config(void) {
	UART2_init();
	USART2_clear_CR1();
	USART2_enable();
	USART2_set_word_length(USART2_CR1_M_WORD_LENGTH_8);
	USART2_set_default_baud_rate();
	USART2_enable_transmitter();
	USART2_enable_receiver();
}


/**
 * @brief Sends a single character over UART2
 * @param c The character to send
 */
void UART2_sendChar(uint32_t c) {
    USART2->DR = c; // Load the data into the data register
    while (!(USART2->SR & (1 << 6))); // Wait until transmission is complete
}

/**
 * @brief Sends a string over UART2
 * @param string The null-terminated string to send
 */
void UART2_sendString(char *string) {
    while ((*string) != '\0') {
        UART2_sendChar(*string);
        string++;
    }
}

/**
 * @brief Receives a single character from UART2
 * @return The received character
 */
uint8_t UART2_getchar(void) {
    while (!(USART2->SR & (1 << 5))); // Wait until data is received
    return USART2->DR;
}

/**
 * @brief Receives a string from UART2
 * @param passwd Array to store the received string
 */
void UART2_getString(char string[], uint32_t input_size) {
    uint8_t len = input_size; // Maximum password size
    for (int i = 0; i < len-1; i++) {
        string[i] = UART2_getchar();
        if (string[i] == NEWLINE_CHARACTER) {
            UART2_sendString("\n\r");
        	string[i] = NULL_CHARACTER;
        	return;
        }
        UART2_sendChar(string[i]); // Echo back the received character
    }
}
