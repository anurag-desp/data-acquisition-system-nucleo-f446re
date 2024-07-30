/*
 * gpio.h
 *
 * Created on: Jul 28, 2024
 * Author: Anurag
 *
 * Documentation: i3ye
 * This header file defines types and functions for GPIO configuration
 * and manipulation on an STM32 microcontroller.
 */

#ifndef GPIO_H_
#define GPIO_H_


/**
 * @brief Enumeration of all GPIO pins across all ports
 *
 * Each pin is assigned a unique number from 0 to 127
 */
typedef enum {
    PA0  = 0,
    PA1  = 1,
    PA2  = 2,
    PA3  = 3,
    PA4  = 4,
    PA5  = 5,
    PA6  = 6,
    PA7  = 7,
    PA8  = 8,
    PA9  = 9,
    PA10 = 10,
    PA11 = 11,
    PA12 = 12,
    PA13 = 13,
    PA14 = 14,
    PA15 = 15,
    PB0  = 16,
    PB1  = 17,
    PB2  = 18,
    PB3  = 19,
    PB4  = 20,
    PB5  = 21,
    PB6  = 22,
    PB7  = 23,
    PB8  = 24,
    PB9  = 25,
    PB10 = 26,
    PB11 = 27,
    PB12 = 28,
    PB13 = 29,
    PB14 = 30,
    PB15 = 31,
    PC0  = 32,
    PC1  = 33,
    PC2  = 34,
    PC3  = 35,
    PC4  = 36,
    PC5  = 37,
    PC6  = 38,
    PC7  = 39,
    PC8  = 40,
    PC9  = 41,
    PC10 = 42,
    PC11 = 43,
    PC12 = 44,
    PC13 = 45,
    PC14 = 46,
    PC15 = 47,
    PD0  = 48,
    PD1  = 49,
    PD2  = 50,
    PD3  = 51,
    PD4  = 52,
    PD5  = 53,
    PD6  = 54,
    PD7  = 55,
    PD8  = 56,
    PD9  = 57,
    PD10 = 58,
    PD11 = 59,
    PD12 = 60,
    PD13 = 61,
    PD14 = 62,
    PD15 = 63,
    PE0  = 64,
    PE1  = 65,
    PE2  = 66,
    PE3  = 67,
    PE4  = 68,
    PE5  = 69,
    PE6  = 70,
    PE7  = 71,
    PE8  = 72,
    PE9  = 73,
    PE10 = 74,
    PE11 = 75,
    PE12 = 76,
    PE13 = 77,
    PE14 = 78,
    PE15 = 79,
    PF0  = 80,
    PF1  = 81,
    PF2  = 82,
    PF3  = 83,
    PF4  = 84,
    PF5  = 85,
    PF6  = 86,
    PF7  = 87,
    PF8  = 88,
    PF9  = 89,
    PF10 = 90,
    PF11 = 91,
    PF12 = 92,
    PF13 = 93,
    PF14 = 94,
    PF15 = 95,
    PG0  = 96,
    PG1  = 97,
    PG2  = 98,
    PG3  = 99,
    PG4  = 100,
    PG5  = 101,
    PG6  = 102,
    PG7  = 103,
    PG8  = 104,
    PG9  = 105,
    PG10 = 106,
    PG11 = 107,
    PG12 = 108,
    PG13 = 109,
    PG14 = 110,
    PG15 = 111,
    PH0  = 112,
    PH1  = 113,
    PH2  = 114,
    PH3  = 115,
    PH4  = 116,
    PH5  = 117,
    PH6  = 118,
    PH7  = 119,
    PH8  = 120,
    PH9  = 121,
    PH10 = 122,
    PH11 = 123,
    PH12 = 124,
    PH13 = 125,
    PH14 = 126,
    PH15 = 127
} GPIOx_Pin_Type;

/**
 * @brief Enumeration of GPIO ports
 *
 * Defines the available GPIO ports from A to H
 */
typedef enum {
	PA = 0,
	PB = 1,
	PC = 2,
	PD = 3,
	PE = 4,
	PF = 5,
	PG = 6,
	PH = 7,
} GPIOx_Ports_Type;

// Constants for GPIO configuration
#define NUM_PORTS               8u
#define NUM_PINS_PER_PORT       16u
#define TOTAL_PINS              128u

// GPIO mode definitions
#define MODER_INPUT                  (0X00000000)
#define MODER_OUTPUT                 (GPIO_MODER_MODER0_0)
#define MODER_AF                     (GPIO_MODER_MODER0_1)
#define MODER_ANALOG                 (GPIO_MODER_MODER0)

// GPIO output type definitions
#define OTYPER_PUSH_PULL             (0X00000000)
#define OTYPER_OPEN_DRAIN            (GPIO_MODER_MODER0_0)

// GPIO output speed definitions
#define OSPEEDR_LOW                  (0X00000000)
#define OSPEEDR_MEDIUM               (GPIO_MODER_MODER0_0)
#define OSPEEDR_FAST                 (GPIO_MODER_MODER0_1)
#define OSPEEDR_HIGH                 (GPIO_MODER_MODER0)

// GPIO pull-up/pull-down definitions
#define PUPDR_NO_PU_PD               (0X00000000)
#define PUPDR_PU                     (GPIO_MODER_MODER0_0)
#define PUPDR_PD                     (GPIO_MODER_MODER0_1)
#define PUPDR_RESERVED               (GPIO_MODER_MODER0)

// Alternate function definitions
#define AF0                          ((uint8_t)0)
#define AF1                          ((uint8_t)1)
#define AF2                          ((uint8_t)2)
#define AF3                          ((uint8_t)3)
#define AF4                          ((uint8_t)4)
#define AF5                          ((uint8_t)5)
#define AF6                          ((uint8_t)6)
#define AF7                          ((uint8_t)7)
#define AF8                          ((uint8_t)8)
#define AF9                          ((uint8_t)9)
#define AF10                         ((uint8_t)10)
#define AF11                         ((uint8_t)11)
#define AF12                         ((uint8_t)12)
#define AF13                         ((uint8_t)13)
#define AF14                         ((uint8_t)14)
#define AF15                         ((uint8_t)15)

// Function prototypes for GPIO operations


/**
 * @brief Initialize the specified GPIO port
 * @param gpiox_type The GPIO port to initialize
 */
extern void GPIOx_init(uint8_t gpiox_type);

/**
 * @brief Configure the mode of a GPIO pin
 * @param pin The pin to configure
 * @param mode The mode to set (input, output, alternate function, or analog)
 */
extern void GPIOx_config_mode(uint8_t pin, uint8_t mode);

/**
 * @brief Configure the output type of a GPIO pin
 * @param pin The pin to configure
 * @param out_type The output type (push-pull or open-drain)
 */
extern void GPIOx_config_output_type(uint8_t pin, uint8_t out_type);

/**
 * @brief Configure the output speed of a GPIO pin
 * @param pin The pin to configure
 * @param out_speed The output speed (low, medium, fast, or high)
 */
extern void GPIOx_config_output_speed(uint8_t pin, uint8_t out_speed);

/**
 * @brief Configure the pull-up/pull-down of a GPIO pin
 * @param pin The pin to configure
 * @param pupd The pull-up/pull-down configuration
 */
extern void GPIOx_config_pupd(uint8_t pin, uint8_t pupd);

/**
 * @brief Configure the alternate function of a GPIO pin
 * @param pin The pin to configure
 * @param alternate_function The alternate function to set
 */
extern void GPIOx_config_alternate_function(uint8_t pin, uint8_t alternate_function);

/**
 * @brief Set the output data register (ODR) of a GPIO pin
 * @param pin The pin to set
 */
extern void GPIOx_set_odr(uint8_t pin);

/**
 * @brief Reset the output data register (ODR) of a GPIO pin
 * @param pin The pin to reset
 */
extern void GPIOx_reset_odr(uint8_t pin);

/**
 * @brief Get the input data register (IDR) value of a GPIO pin
 * @param pin The pin to read
 * @return The input state of the pin
 */
extern uint8_t GPIOx_get_idr(uint8_t pin);

#endif /* GPIO_H_ */
