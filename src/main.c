#include "battery_indic.h"
#include "mpr121.h"
#include "ssd1306.h"
#include "gesture.h"
#include "system_time.h"
#include <util/delay.h>
#include "images.h"
#include <stdio.h>

#define MPR121_ADDRESS 0x5A

#define TOGGLE_CHARGER_PIN() (PORTD ^= (1 << PD4))

void display_trace(Gesture_Observer* observer);

void gesture_setup(Gesture* gesture1, Gesture* gesture2, Gesture* gesture3);
void periph_setup(void);

int main(void)
{
  uint16_t pressed_pads = 0;
  uint16_t newly_pressed = 0;
  uint16_t prev_pressed_pads = 0;
  uint16_t baselines[12];
  uint8_t observer_result = 0;

  periph_setup();

  Gesture_Observer observer = observer_create();
  Gesture gesture1 = gesture_create(1, 5, 4);
  Gesture gesture2 = gesture_create(2, 0, 0);

  gesture_setup(&gesture1, &gesture2, 0);

  observer_add_gesture(&observer, gesture1);
  observer_add_gesture(&observer, gesture2);

  tTime gesture_timeout = 200 * TIMER1_MILLISECOND;
  tTime last_press = 0;

  tTime charger_timeout = 1 * TIMER1_SECOND;
  tTime last_reset = 0;

  mpr121_get_filtered_baseline(MPR121_ADDRESS, baselines);

  while(1)
  {
    oled_set_cursor(0,0);
    oled_write_image(sleeping);
    _delay_ms(500);
    oled_set_cursor(0,0);
    oled_write_image(sleeping2);
    _delay_ms(500);
    oled_set_cursor(0,0);
    oled_write_image(sleeping3);
    _delay_ms(500);
    oled_set_cursor(0,0);
    oled_write_image(resting);
    _delay_ms(500);
    oled_set_cursor(0,0);
    oled_write_image(shocked);
    _delay_ms(500);
    oled_set_cursor(0,0);
    //oled_write_image(shocked2);
    _delay_ms(500);
    oled_set_cursor(0,0);
    //oled_write_image(relieved);
    _delay_ms(500);
    oled_set_cursor(0,0);
    //oled_write_image(relieved2);
    _delay_ms(500);
    oled_set_cursor(0,0);
    //oled_write_image(confused);
    _delay_ms(500);
    oled_set_cursor(0,0);
    //oled_write_image(confused2);
    _delay_ms(500);
  }

  while(0)
  {
    mpr121_get_filtered_pressed(MPR121_ADDRESS, baselines, &pressed_pads);
  }

  #if 0
  while(1)
  {
    mpr121_get_filtered_pressed(MPR121_ADDRESS, baselines, &pressed_pads);
    newly_pressed = mpr121_get_specific_pressed(pressed_pads);

    // We have to reset the charger module every few seconds to keep it on
    if(time_passed(last_reset) > charger_timeout)
    {
      TOGGLE_CHARGER_PIN();
    }

    // If the gesture times out, we evaluate it
    if(time_passed(last_press) > gesture_timeout)
    {
      observer_result = observer_get_result(&observer);
      last_press = timer1_get_time();

      if(observer_result)
      {
        // Do appropriate action to the gesture
      }
      observer_clear_trace(&observer);
      observer_result = 0;
    }
    
    // Check for new presses
    if(newly_pressed == -1)
    {
      // do nothing
    }
    else
    {
      // If theres a new press inform the timeout and
      // the gesture observer
      last_press = timer1_get_time();

      if(prev_pressed_pads != pressed_pads)
      {
        // New Button has been Pressed
        observer_inform(&observer, newly_pressed);
      }
      prev_pressed_pads = pressed_pads;
    }
  }
  #endif
}


void display_trace(Gesture_Observer* observer)
{
  for(uint8_t i = 0; i < observer->trace_size; i++)
  {
    oled_write_int(observer->current_trace[i]);
  }
  if(observer->trace_size == MAX_TRACE)
  {
    oled_clear();
    observer_clear_trace(observer);
  }
}

void periph_setup(void)
{
  i2c_init();
  init_system_tick();
  setup_battery_indic();
  mpr121_setup(MPR121_ADDRESS, ELE_EN(0b1100), DEBOUNCE_DT(0b000) | DEBOUNCE_DR(0b000), ESI(0) | SFI(0b00), FFI(0b00) | CDC(0b111111));
  mpr121_set_threshold(MPR121_ADDRESS, 0, 0);
  oled_init();
  oled_clear();

  DDRD |= (1 << PD4);
}

void gesture_setup(Gesture* gesture1, Gesture* gesture2, Gesture* gesture3)
{
  gesture_add_trace(gesture1, 9);
  gesture_add_trace(gesture1, 5);
  gesture_add_trace(gesture1, 1);
  gesture_add_trace(gesture1, 2);
  gesture_add_trace(gesture1, 3);
  gesture_add_trace(gesture1, 7);
  gesture_add_trace(gesture1, 11);
  gesture_add_trace(gesture1, 10);
  gesture_add_trace(gesture1, 9);

  gesture_add_trace(gesture2, 5);
}