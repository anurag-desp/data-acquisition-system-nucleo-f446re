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

#include "stm32f446xx.h" // Include STM32F446xx specific definitions

// Define the maximum password size
#define MAX_PWD_SIZE 9

/**
 * @brief Configures UART2 for communication
 * This function sets up UART2 with predefined settings (baud rate, data bits, etc.)
 */
void UART2_config();

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
void UART2_getString(char str[]);

#endif /* USART_H_ */
