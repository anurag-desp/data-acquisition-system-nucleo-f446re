/**
 * @file: usart.h
 *
 * @date: Jul 29, 2024
 * @author: Anurag
 * @documentation: Aayush
 *
 * This header file declares the interface for UART2 configuration and communication
 * functions for an STM32 microcontroller.
*/

#ifndef USART_H_
#define USART_H_

#include <stdint.h>
#include "stm32f446xx.h" // Include STM32F446xx specific definitions
#include "gpio.h"

// ANSI escape codes for terminal control and text colors
#define clearScreen() printf("\033[H\033[J")

// Normal color
#define KNRM  "\x1B[0m"   	// Normal (default) color
#define KRED  "\x1B[91m"  	// Red
#define KGRN  "\x1B[92m"  	// Green
#define KYEL  "\x1B[93m"  	// Yellow
#define KBLU  "\x1B[94m"  	// Blue
#define KMAG  "\x1B[95m"  	// Magenta
#define KCYN  "\e[0;96m"  	// Cyan
#define KWHT  "\x1B[97m"  	// White

// Bold-High Intensity
#define BHBLK "\e[1;90m"
#define BHRED "\e[1;91m"
#define BHGRN "\e[1;92m"
#define BHYEL "\e[1;93m"
#define BHBLU "\e[1;94m"
#define BHMAG "\e[1;95m"
#define BHCYN "\e[1;96m"
#define BHWHT "\e[1;97m"


#define MAX_COLOR_CODE_LENGTH 8
#define MAX_INPUT_SIZE (0xFFFFFFFF)
#define NEWLINE_CHARACTER '\n'
#define NULL_CHARACTER '\0'

// USART2 configuration constants
#define USART2_CR1_M_WORD_LENGTH_8    ((uint8_t) 0)
#define USART2_CR1_M_WORD_LENGTH_9    ((uint8_t) 1)

// Function prototypes for UART2 operations

/**
 * @brief Initialize UART2
*/
extern void UART2_init(void);

/**
 * @brief Clear USART2 CR1 register
*/
extern void USART2_clear_CR1(void);

/**
 * @brief Enable USART2
*/
extern void USART2_enable(void);

/**
 * @brief Set USART2 word length
 * @param length Word length (8 or 9 bits)
*/
extern void USART2_set_word_length(uint8_t length);

/**
 * @brief Enable USART2 transmitter
*/
extern void USART2_enable_transmitter(void);

/**
 * @brief Enable USART2 receiver
*/
extern void USART2_enable_receiver(void);

/**
 * @brief Set default baud rate for USART2
*/
extern void USART2_set_default_baud_rate(void);

/**
 * @brief Quick default configuration for USART2
*/
extern void USART2_quick_default_config(void);

/**
 * @brief Sends a single character over UART2
 * @param c The character to send (as a 32-bit unsigned integer)
*/
void UART2_sendChar(uint32_t c);

/**
 * @brief Sends a string over UART2
 * @param string Pointer to the null-terminated string to send
*/
void UART2_sendString(char *string);

/**
 * @brief Receives a single character from UART2
 * @return The received character as an 8-bit unsigned integer
*/
uint8_t UART2_getchar(void);

/**
 * @brief Receives a string from UART2
 * @param string Array to store the received string
 * @param input_size Maximum size of the input string
*/
void UART2_getString(char string[], uint32_t input_size);

#endif /* USART_H_ */
