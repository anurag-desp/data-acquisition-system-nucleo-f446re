/*
 * usart.h
 *
 * Created on: Jul 30, 2024
 * Author: i3ye
 *
 * This header file declares the interface for UART2 configuration and communication
 * functions for an STM32 microcontroller.
 */

#ifndef USART_H_
#define USART_H_

#include <stdint.h>
#include "stm32f446xx.h" // Include STM32F446xx specific definitions
#include "gpio.h"

#define clearScreen() printf("\033[H\033[J")
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[91m"
#define KGRN  "\x1B[92m"
#define KYEL  "\x1B[93m"
#define KBLU  "\x1B[94m"
#define KMAG  "\x1B[95m"
#define KCYN  "\x1B[96m"
#define KWHT  "\x1B[97m"

#define MAX_COLOR_CODE_LENGTH 8

#define MAX_INPUT_SIZE (0xFFFFFFFF)
#define NEWLINE_CHARACTER '\n'
#define NULL_CHARACTER '\0'

#define USART2_CR1_M_WORD_LENGTH_8				((uint8_t) 0)
#define USART2_CR1_M_WORD_LENGTH_9				((uint8_t) 1)



extern void UART2_init(void);

extern void USART2_clear_CR1(void);

extern void USART2_enable(void);

extern void USART2_set_word_length(uint8_t length);

extern void USART2_enable_transmitter(void);

extern void USART2_enable_receiver(void);

extern void USART2_set_default_baud_rate(void);

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
 * @param passwd Array to store the received string
 */
void UART2_getString(char string[], uint32_t input_size);

#endif /* USART_H_ */
