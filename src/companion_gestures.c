#include "companion_gestures.h"

Companion_Gestures companion_gestures_create()
{
  Companion_Gestures temp;
  temp.observer = observer_create();

  mpr121_setup(MPR121_ADDRESS, ELE_EN(0b1100), DEBOUNCE_DT(0b000) | DEBOUNCE_DR(0b000), ESI(0) | SFI(0b00), FFI(0b00) | CDC(0b111111));
  mpr121_set_threshold(MPR121_ADDRESS, 0, 0);
  mpr121_get_filtered_baseline(MPR121_ADDRESS, temp.baselines);

  temp.last_press = 0;
  temp.last_gesture_result = 0;
  temp.pressed_pads = 0;
  temp.newly_pressed = 0;
  temp.prev_pressed_pads = 0;

  return temp;
}

uint8_t companion_gestures_run(Companion_Gestures* cg)
{
  uint8_t temp_gesture_result = 0;

  mpr121_get_filtered_pressed(MPR121_ADDRESS, cg->baselines,  &cg->pressed_pads);
  cg->newly_pressed = mpr121_get_specific_pressed(cg->pressed_pads);

  // If the gesture times out, we evaluate it
  if(time_passed(cg->last_press) > GESTURE_TIMEOUT)
  {
    cg->last_gesture_result = observer_get_result(&cg->observer);
    cg->last_press = timer1_get_time();

    if(cg->last_gesture_result)
    {
      // Do appropriate action to the gesture
      temp_gesture_result = cg->last_gesture_result;
      cg->last_gesture_result = 0;
      observer_clear_trace(&cg->observer);
      return temp_gesture_result;
    }
  }
  
  // Check for new presses
  if(cg->newly_pressed == -1)
  {
    // do nothing
  }
  else
  {
    // If theres a new press inform the timeout and
    // the gesture observer
    cg->last_press = timer1_get_time();

    if(cg->prev_pressed_pads != cg->pressed_pads)
    {
      // New Button has been Pressed
      observer_inform(&cg->observer, cg->newly_pressed);
    }
    cg->prev_pressed_pads = cg->pressed_pads;
  }

  return 0;
}
