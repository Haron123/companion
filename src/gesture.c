#include "gesture.h"

/**
 * @brief compares 2 arrays
 * @param arr1 the first array
 * @param arr1_size size of the first array
 * @param arr2 the second array
 * @param arr2_size size of the second array
 * @retval a percentage of match between 0-100 representing percent
*/
static uint8_t compare_array(uint8_t* arr1, uint8_t arr1_size, uint8_t* arr2, uint8_t arr2_size)
{
  int16_t matches = 0;
  uint8_t min_size = arr1_size;
  uint8_t max_size = arr2_size;

  uint8_t* bigger_array = arr2;
  uint8_t* smaller_array = arr1;

  uint8_t index_increase = 0;

  if(min_size > arr2_size)
  {
    max_size = arr1_size;
    bigger_array = arr1;
    smaller_array = arr2;
  }

  for(uint8_t i = 0; i < max_size; i++)
  {
    if(smaller_array[i - index_increase] == bigger_array[i])
    {
      matches++;
    }
    else
    {
      index_increase++;
      matches--;

    }
  }
  if(matches < 0)
  {
    matches = 0;
  }

  matches *= 100;

  return matches/max_size;
}

/**
 * @brief Creates a gesture with the given id
 * @param id the id of the gesture
 * @param accuracy_error_allowance determines how many wrong inputs can be done and still be interpreted as right
 * @param size_error_allowance determines how many more/less inputs can be done and still be interpreted as right
 * @retval a gesture with the given id
*/
Gesture gesture_create(uint8_t id, uint8_t accuracy_error_allowance, uint8_t size_error_allowance)
{
  Gesture temp;
  temp.id = id;
  temp.gesture_size = 0;
  temp.accuracy_error_allowance = accuracy_error_allowance;
  temp.size_error_allowance = size_error_allowance;

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
  if(observer->trace_size <= MAX_TRACE)
  {
    if(observer->trace_size == 0 || (observer->trace_size > 0 && observer->current_trace[observer->trace_size-1] != pressed_button))
    {
      observer->current_trace[observer->trace_size++] = pressed_button;
    }
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
  uint8_t gesture_size = 0;
  uint8_t trace_size = 0;
  uint8_t accuracy = 0;
  uint8_t size_error = 0;

  for(uint8_t i = 0; i < observer->gesture_amount; i++)
  {
    gesture_size = observer->gestures[i].gesture_size;
    trace_size = observer->trace_size;

    accuracy = observer->gestures[i].accuracy_error_allowance;
    size_error = observer->gestures[i].size_error_allowance;

    if(gesture_size >= trace_size - size_error && gesture_size <= trace_size + size_error)
    {
      if(compare_array((uint8_t*)(&(observer->gestures[i].trace)),gesture_size, observer->current_trace, trace_size) >= 
      (((gesture_size-accuracy) * 100) / gesture_size))
      {
        return observer->gestures[i].id;
      }
    }
  }

  return 0;
}