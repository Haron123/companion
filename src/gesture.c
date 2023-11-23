#include "gesture.h"

/**
 * @brief compares 2 arrays
 * @param arr1 the first array
 * @param arr1_size size of the first array
 * @param arr2 the second array
 * @param arr2_size size of the second array
 * @retval 1 if theyre the same, 0 if theyre different
*/
static uint8_t compare_array(uint8_t* arr1, uint8_t arr1_size, uint8_t* arr2, uint8_t arr2_size)
{
  if(arr1_size != arr2_size)
  {
    return 0;
  }

  for(uint8_t i = 0; i < arr1_size; i++)
  {
    if(arr1[i] != arr2[i])
    {
      return 0;
    }
  }

  return 1;
}

/**
 * @brief Creates a gesture with the given id
 * @retval a gesture with the given id
*/
Gesture gesture_create(uint8_t id)
{
  Gesture temp;
  temp.id = id;
  temp.gesture_size = 0;

  return temp;
}

void gesture_add_trace(Gesture* gesture, Button trace)
{
  if(gesture->gesture_size < MAX_TRACE)
  {
    gesture->trace[gesture->gesture_size++] = trace;
  }
}

/**
 * @brief creates an observer with default values
 * @retval the created observer
*/
Gesture_Observer observer_create(Gesture_Observer* observer)
{
  Gesture_Observer temp;
  temp.trace_size = 0;
  temp.gesture_amount = 0;

  return temp;
}

/**
 * @brief adds a previously defined Gesture to the observer
 * @param gesture copy of a Gesture thats to add
*/
void observer_add_gesture(Gesture_Observer* observer, Gesture gesture)
{
  observer->gestures[observer->gesture_amount++] = gesture;
}

/**
 * @brief informs the observer about a newly pressed button
 * @param pressed_button the number of the newly pressed Button
*/
void observer_inform(Gesture_Observer* observer, Button pressed_button)
{
  if(observer->trace_size < MAX_TRACE)
  {
    observer->current_trace[observer->trace_size++] = pressed_button;
  }
}

/**
 * @brief clears the trace of the observer. Useful when 
 * a Timeout for the Gesture occurs
*/
void observer_clear_trace(Gesture_Observer* observer)
{
  observer->trace_size = 0;
}

/**
 * @brief check if the current trace of the observer has a match 
 * with the gestures it contains.
 * @retval returns the id of the gesture which the trace matched with
*/
uint8_t observer_get_result(Gesture_Observer* observer)
{
  for(uint8_t i = 0; i < observer->gesture_amount; i++)
  {
    if(compare_array((uint8_t*)(&(observer->gestures[i].trace)), observer->gestures[i].gesture_size, observer->current_trace, observer->trace_size))
    {
      return observer->gestures[i].id;
    }
  }

  return 0;
}