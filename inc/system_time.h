#ifndef SYSTEM_TIME_H
#define SYSTEM_TIME_H

#include <stdint.h>
#include <avr/io.h>

#define MAX_TIME ((1ULL << (sizeof(tTime) * 8)) - 1)

#define TIMER1_CLOCK 16000000

// Both Macros have to be updated at the same time
// one is used for the register value
// the other is used to make further calculations possible
#define TIMER1_PRESCALER_REGVAL TIMER1_PRESCALER_8
#define TIMER1_PRESCALER_NUMBER 8

#define TIMER1_SECOND (TIMER1_CLOCK / TIMER1_PRESCALER_NUMBER)
#define TIMER1_MILLISECOND (TIMER1_SECOND / 1000)
#define TIMER1_MICROSECOND (TIMER1_MILLISECOND / 1000)

// Mapping Prescaler to actual register values
// For the atmega328p Timer1
#if(mcu == atmega328p)
#define TIMER1_PRESCALER_OFF 0b0000
#define TIMER1_PRESCALER_1 0b0001
#define TIMER1_PRESCALER_8 0b0010
#define TIMER1_PRESCALER_64 0b0011
#define TIMER1_PRESCALER_256 0b0100
#define TIMER1_PRESCALER_1024 0b0101
#endif


// Simplifies the transition to different value ranges and aids in clarity
// Also helps the macros calculate MAXTIME
typedef uint16_t tTime;

/**
 * @brief Initializes the system tick timer.
 * The system tick starts running as soon as this function is executed.
 * It is used to work with time without using an additional timer.
 * 
 * system_tick is measured in milli seconds
 */
void init_system_tick();

/**
 * @brief Pauses the system for the specified amount of time.
 * @param ms The time to wait, specified in milliseconds.
 * @retval None
 */
void delay_ms(tTime ms);

/**
 * @brief Pauses the system for the specified amount of time.
 * @param us The time to wait, specified in microseconds.
 * @retval None
 */
void delay_us(tTime us);

/**
 * @brief Retrieves the current value of the system time in ms
 * @retval The current value of the system time in ms.
 */
tTime timer1_get_time();

/**
 * @brief Compares the current time to a specified time.
 * @param since The Time to compare to
 * @retval the time that passed in the moment of the function call, since "since"
 */
tTime time_passed(tTime since);

#endif
