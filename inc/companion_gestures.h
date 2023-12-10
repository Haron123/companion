#ifndef COMPANION_GESTURES_H
#define COMPANION_GESTURES_H

#include "gesture.h"
#include "system_time.h"
#include "mpr121.h"

#define MPR121_ADDRESS 0x5A

#define GESTURE_TIMEOUT 200 * TIMER1_MILLISECOND

typedef struct Companion_Gestures
{
  Gesture_Observer observer;
  tTime last_press;
  uint8_t last_gesture_result;
  
  uint16_t pressed_pads;
  uint16_t newly_pressed;
  uint16_t prev_pressed_pads;
  uint16_t baselines[12];
} Companion_Gestures;

Companion_Gestures companion_gestures_create();

uint8_t companion_gestures_run(Companion_Gestures* cg);



#endif