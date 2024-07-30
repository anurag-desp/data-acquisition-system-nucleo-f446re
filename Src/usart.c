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
void UART2_Config(void) {
    // Enable USART2 clock
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    // Enable GPIOA clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Configure PA2 (RX) and PA3 (TX) for UART2
    GPIOA->MODER |= GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1; // Set to alternate function mode
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2 | GPIO_OSPEEDER_OSPEEDR3; // Set to high speed
    GPIOA->AFR[0] |= (7 << 8) | (7 << 12); // Set alternate function to UART2 (AF7)

    // Configure UART2
    USART2->CR1 = 0x00; // Reset the control register
    USART2->CR1 |= USART_CR1_UE; // Enable UART
    USART2->CR1 &= ~USART_CR1_M; // Set to 8 data bits
    USART2->BRR = (7 << 0) | (24 << 4); // Set baud rate to 115200 (assuming PCLK1 at 45MHz)
    USART2->CR1 |= (1 << 2); // Enable receiver
    USART2->CR1 |= (1 << 3); // Enable transmitter
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
void UART2_getString(char str[]) {
    uint8_t len = MAX_PWD_SIZE; // Maximum password size
    for (int i = 0; i < len-1; i++) {
        str[i] = UART2_getchar();
        UART2_sendChar(str[i]); // Echo back the received character
    }
}
