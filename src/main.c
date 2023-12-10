#include "battery_indic.h"
#include "ssd1306.h"
#include "gesture.h"
#include "system_time.h"
#include <util/delay.h>
#include "images.h"
#include "companion_gestures.h"
#include <stdio.h>

#define TOGGLE_CHARGER_PIN() (PORTD ^= (1 << PD4))

void display_trace(Gesture_Observer* observer);

void gesture_setup(Gesture* gesture1, Gesture* gesture2, Gesture* gesture3);
void periph_setup(void);

int main(void)
{
  periph_setup();

  Companion_Gestures cg = companion_gestures_create();
  
  Gesture gesture1 = gesture_create(1, 5, 4);
  Gesture gesture2 = gesture_create(2, 0, 0);

  gesture_setup(&gesture1, &gesture2, 0);

  observer_add_gesture(&cg.observer, gesture1);
  observer_add_gesture(&cg.observer, gesture2);

  tTime charger_timeout = 1 * TIMER1_SECOND;
  tTime last_reset = 0;

  while(0)
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
    oled_write_image(shocked2);
    _delay_ms(500);
    oled_set_cursor(0,0);
    oled_write_image(relieved);
    _delay_ms(500);
    oled_set_cursor(0,0);
    oled_write_image(relieved2);
    _delay_ms(500);
    oled_set_cursor(0,0);
    oled_write_image(confused);
    _delay_ms(500);
    oled_set_cursor(0,0);
    oled_write_image(confused2);
    _delay_ms(500);
  }

  #if 1
  while(1)
  {
    // We have to reset the charger module every few seconds to keep it on
    if(time_passed(last_reset) > charger_timeout)
    {
      TOGGLE_CHARGER_PIN();
    }

    companion_gestures_run(&cg);
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