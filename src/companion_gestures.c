#include "companion_gestures.h"

void companion_gestures_create(Companion_Gestures* cg)
{
  cg->observer = observer_create();

  cg->last_press = 0;
  cg->last_gesture_result = 0;
  cg->pressed_pads = 0;
  cg->newly_pressed = 0;
  cg->prev_pressed_pads = 0;
}

static uint8_t check_gesture_timeout(Companion_Gestures* cg)
{
  uint8_t final_trace_size = 0;

  // If the gesture times out, we evaluate it
  if(time_passed(cg->last_press) > GESTURE_TIMEOUT)
  {
    // Get the gesture result and update the last pressed parameter
    cg->last_gesture_result = observer_get_result(&cg->observer);
    cg->last_press = timer1_get_time();

    // Save and clear the trace
    final_trace_size = cg->observer.trace_size;
    
    observer_clear_trace(&cg->observer);

    if(cg->last_gesture_result)
    {
      // Do appropriate action to the gesture
      return 1;
    }
    else if(final_trace_size >= 10)
    {
      return 2;
    }
  }

  return 0;
}

uint8_t companion_gestures_run(Companion_Gestures* cg)
{
  mpr121_get_filtered_pressed(MPR121_ADDRESS, cg->baselines,  &cg->pressed_pads);
  
  // Check for new presses
  cg->newly_pressed = mpr121_get_specific_pressed(cg->pressed_pads);

  if(cg->newly_pressed != -1)
  {
    // If theres a new press inform the timeout and
    // the gesture observer
    cg->last_press = timer1_get_time();
    observer_inform(&cg->observer, cg->newly_pressed);
  }

  return check_gesture_timeout(cg);
}
