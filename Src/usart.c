/**
 * @file: usart.c
 * @date: Jul 30, 2024
 * @author: Anurag
 * @documentation: Aayush
 *
 * This file contains the implementation of UART2 configuration and communication
 * functions for an STM32 microcontroller.
*/

#include "usart.h"

/**
 * @brief Initialize UART2 and configure related GPIO pins
 *
 * This function enables the USART2 clock, initializes and configures PA2 and PA3
 * for alternate function (UART), and sets up the basic UART2 configuration.
*/
void UART2_init(void) {
    // Enable USART2 clock
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    // Initialize and configure GPIO pins for UART2
    GPIOx_init(PA);
    GPIOx_config_mode(PA2, MODER_AF);
    GPIOx_config_mode(PA3, MODER_AF);
    GPIOx_config_output_speed(PA2, OSPEEDR_HIGH);
    GPIOx_config_output_speed(PA3, OSPEEDR_HIGH);
    GPIOx_config_alternate_function(PA2, AF7);
    GPIOx_config_alternate_function(PA3, AF7);
}

/**
 * @brief Clear USART2 CR1 register
 *
 * This function resets the USART2 CR1 register to its default state.
*/
void USART2_clear_CR1(void) {
    USART2->CR1 = 0x00;
}

/**
 * @brief Enable USART2
 *
 * This function enables the USART2 peripheral.
*/
void USART2_enable(void) {
    USART2->CR1 |= USART_CR1_UE;
}

/**
 * @brief Set USART2 word length
 * @param length Word length (8 or 9 bits)
 *
 * This function sets the word length for USART2 communication.
*/
void USART2_set_word_length(uint8_t length) {
    if (length != USART2_CR1_M_WORD_LENGTH_9)
        USART2->CR1 &= ~USART_CR1_M;
    else
        USART2->CR1 |=  USART_CR1_M;
}

/**
 * @brief Enable USART2 transmitter
 *
 * This function enables the transmitter for USART2.
*/
void USART2_enable_transmitter(void) {
    USART2->CR1 |= (1 << PA2);
}

/**
 * @brief Enable USART2 receiver
 *
 * This function enables the receiver for USART2.
*/
void USART2_enable_receiver(void) {
    USART2->CR1 |= (1 << PA3);
}

/**
 * @brief Set default baud rate for USART2
 *
 * This function sets the default baud rate (115200) for USART2.
*/
void USART2_set_default_baud_rate(void) {
    USART2->BRR = (7 << 0) | (24 << 4);
}

/**
 * @brief Quick default configuration for USART2
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
 * @brief Send a single character over UART2
 * @param c The character to send
 * 
 * This function sends a single character over UART2 and waits for the transmission to complete.
*/
void UART2_sendChar(uint32_t c) {
    USART2->DR = c; // Load the data into the data register
    while (!(USART2->SR & (1 << 6))); // Wait until transmission is complete
}

/**
 * @brief Send a string over UART2
 * @param string The null-terminated string to send
 *
 * This function sends a null-terminated string over UART2.
*/
void UART2_sendString(char *string) {
    while ((*string) != '\0') {
        UART2_sendChar(*string);
        string++;
    }
}

/**
 * @brief Receive a single character from UART2
 * @return The received character
 *
 * This function waits for a character to be received on UART2 and returns it.
*/
uint8_t UART2_getchar(void) {
    while (!(USART2->SR & (1 << 5))); // Wait until data is received
    return USART2->DR;
}

/**
 * @brief Receive a string from UART2
 * @param string Array to store the received string
 * @param input_size Maximum size of the input string
 *
 * This function receives a string from UART2, echoes back each character,
 * and terminates the string when a newline character is received or the
 * maximum input size is reached.
*/
void UART2_getString(char string[], uint32_t input_size) {
    uint8_t len = input_size; // Maximum input size
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