#ifndef GESTURE_H
#define GESTURE_H

#include <stdint.h>

typedef int8_t Button;

#define MAX_TRACE 15
#define MAX_GESTURES 5

#define ACCURACY_ERROR_ALLOWANCE 3
#define SIZE_ERROR_ALLOWANCE 3

typedef struct Gesture
{
  uint8_t accuracy_error_allowance;
  uint8_t size_error_allowance;
  uint8_t id;
  uint8_t gesture_size;
  Button trace[MAX_TRACE];
} Gesture;

typedef struct Gesture_Observer
{
  uint8_t trace_size;
  uint8_t current_trace[MAX_TRACE];

  uint8_t gesture_amount;
  Gesture gestures[MAX_GESTURES];
} Gesture_Observer;

/**
 * @brief Creates a gesture with the given id
 * @retval a gesture with the given id
*/
Gesture gesture_create(uint8_t id, uint8_t accuracy_error_allowance, uint8_t size_error_allowance);

void gesture_add_trace(Gesture* gesture, Button trace);

/**
 * @brief creates an observer with default values
 * @retval the created observer
*/
Gesture_Observer observer_create();

/**
 * @brief adds a previously defined Gesture to the observer
 * @param gesture copy of a Gesture thats to add
*/
void observer_add_gesture(Gesture_Observer* observer, Gesture gesture);

/**
 * @brief informs the observer about a newly pressed button
 * @param pressed_button the number of the newly pressed Button
*/
void observer_inform(Gesture_Observer* observer, Button pressed_button);

/**
 * @brief clears the trace of the observer. Useful when 
 * a Timeout for the Gesture occurs
*/
void observer_clear_trace(Gesture_Observer* observer);

/**
 * @brief check if the current trace of the observer has a match 
 * with the gestures it contains.
 * @retval returns the id of the gesture which the trace matched with
*/
uint8_t observer_get_result(Gesture_Observer* observer);



#endif