#include "battery_indic.h"
#include "ssd1306.h"
#include "gesture.h"
#include "system_time.h"
#include <util/delay.h>
#include "images.h"
#include "companion_gestures.h"
#include <stdio.h>

#define TOGGLE_CHARGER_PIN() (PORTD ^= (1 << PD2))

#define SLEEP_TIMEOUT 30
#define CHARGER_TIMEOUT 500 * TIMER1_MILLISECOND

#define SLEEP_DELAY_ONE 400 * TIMER1_MILLISECOND
#define SLEEP_DELAY_TWO 800 * TIMER1_MILLISECOND
#define SLEEP_DELAY_THREE 1200 * TIMER1_MILLISECOND

void display_trace(Gesture_Observer* observer);

void gesture_setup(Gesture* gesture1, Gesture* gesture2, Gesture* gesture3);
void periph_setup(void);
void show_shocked();
void show_relieved();
void show_confused();
void show_bat();

int main(void)
{
  periph_setup();

  Companion_Gestures cg;
  companion_gestures_create(&cg);
  
  Gesture gesture1 = gesture_create(1, 5, 4);
  Gesture gesture2 = gesture_create(2, 0, 0);
  Gesture gesture3 = gesture_create(3, 2, 2);
  
  gesture_setup(&gesture1, &gesture2, &gesture3);

  observer_add_gesture(&cg.observer, gesture1);
  observer_add_gesture(&cg.observer, gesture2);
  observer_add_gesture(&cg.observer, gesture3);

  tTime last_reset = timer1_get_time();
  tTime idle_time = timer1_get_time();

  uint8_t idle_counter = 0; // Goes up by one every second up to 255, resets if interacted with
  uint8_t draw_flag = 1;
  uint8_t sleep_anim_flag = 0;
  tTime sleep_anim_delay = 0;

  #if 1
  while(1)
  {
    if(cg.baselines[0] == 0 || cg.baselines[0] > 1000)
    {
      mpr121_get_filtered_baseline(MPR121_ADDRESS, cg.baselines);
    }
    
    //oled_set_cursor(0,0);
    //display_baseline(&cg);

    // We have to reset the charger module every few seconds to keep it on
    if(time_passed(last_reset) > CHARGER_TIMEOUT)
    {
      TOGGLE_CHARGER_PIN();
      last_reset = timer1_get_time();
    }

    // Increase idle counter if idle for a second
    if(time_passed(idle_time) > TIMER1_SECOND)
    {
      if(idle_counter < 256)
      {
        idle_counter++;
        idle_time = timer1_get_time();
      }
      else
      {
        idle_counter = SLEEP_TIMEOUT;
      }
    }

    // Debugging
    oled_set_cursor(0,0);
    display_trace(&cg.observer);

    uint8_t gesture_data = companion_gestures_run(&cg);

    // Check if a Gesture was found and handle it
    if(gesture_data == 1)
    {
      // Get out of Idle
      idle_counter = 0;
      idle_time = timer1_get_time();
      draw_flag = 1;

      switch (cg.last_gesture_result)
      {
        case 2:
          show_shocked();
          break;
        case 1:
          show_relieved();
          break;
        case 3:
          show_bat();
          break;
      }
    }
    else if(gesture_data == 2)
    {
      // Confusion was detected
      // Get out of Idle
      idle_counter = 0;
      idle_time = timer1_get_time();

      draw_flag = 1;
      show_confused();
    }

    // Go to sleep
    if(idle_counter > SLEEP_TIMEOUT)
    {
      if(!sleep_anim_flag)
      {
        sleep_anim_delay = timer1_get_time();
        sleep_anim_flag = 1;
      }
      else if(time_passed(sleep_anim_delay) > 0 && time_passed(sleep_anim_delay) < SLEEP_DELAY_ONE)
      {
        oled_set_cursor(0,0);
        oled_write_image(sleeping);
      }
      else if(time_passed(sleep_anim_delay) > SLEEP_DELAY_ONE && time_passed(sleep_anim_delay) < SLEEP_DELAY_TWO)
      {
        oled_set_cursor(0,0);
        oled_write_image(sleeping2);
      }
      else if(time_passed(sleep_anim_delay) > SLEEP_DELAY_TWO)
      {
        oled_set_cursor(0,0);
        oled_write_image(sleeping3);

        if(time_passed(sleep_anim_delay) > SLEEP_DELAY_THREE)
        {
          // Reset the sleep animation
          sleep_anim_flag = 0;
        }
      }
    }
    else if(draw_flag)
    {
      oled_set_cursor(0,0);
      oled_write_image(resting);
      draw_flag = 0;
    }
  }
  #endif
}

void show_shocked()
{
  oled_set_cursor(0,0);
  oled_write_image(shocked);
  _delay_ms(1000);
  oled_set_cursor(0,0);
  oled_write_image(shocked2);
  _delay_ms(400);
  oled_set_cursor(0,0);
  oled_write_image(shocked3);
  _delay_ms(250);
  oled_set_cursor(0,0);
  oled_write_image(shocked4);
  _delay_ms(250);
}

void show_relieved()
{
  oled_set_cursor(0,0);
  oled_write_image(relieved);
  _delay_ms(300);
  oled_set_cursor(0,0);
  oled_write_image(relieved2);
  _delay_ms(300);
  oled_set_cursor(0,0);
  oled_write_image(relieved3);
  _delay_ms(300);
  oled_set_cursor(0,0);
  oled_write_image(relieved4);
  _delay_ms(300);
  oled_set_cursor(0,0);
  oled_write_image(relieved3);
  _delay_ms(300);
  oled_set_cursor(0,0);
  oled_write_image(relieved2);
  _delay_ms(300);
  oled_set_cursor(0,0);
  oled_write_image(relieved);
  _delay_ms(300);
}

void show_confused()
{
  oled_set_cursor(0,0);
  oled_write_image(confused);
  _delay_ms(500);
  oled_set_cursor(0,0);
  oled_write_image(confused2);
  _delay_ms(500);
  oled_set_cursor(0,0);
  oled_write_image(confused);
  _delay_ms(500);
  oled_set_cursor(0,0);
  oled_write_image(confused2);
  _delay_ms(500);
  oled_set_cursor(0,0);
  oled_write_image(confused);
  _delay_ms(500);
}

void show_bat()
{
  oled_set_cursor(0,0);
  uint8_t bat = get_battery_level();

  switch(bat)
  {
    case 0x7: oled_write_image(bat100perc); break;

    case 0x3: oled_write_image(bat50perc); break;

    case 0x1: oled_write_image(bat25perc); break;
  }
  _delay_ms(2000);
}

void display_trace(Gesture_Observer* observer)
{
  for(uint8_t i = 0; i < observer->trace_size; i++)
  {
    oled_write_int(observer->current_trace[i]);
  }
}

void display_baseline(Companion_Gestures* cg)
{
  for(uint8_t i = 0; i < 12; i++)
  {
    oled_write_int(cg->baselines[i]);
  }
}

void periph_setup(void)
{
  i2c_init();
  init_system_tick();
  setup_battery_indic();
  oled_init();
  oled_clear();
  mpr121_setup(MPR121_ADDRESS, ELE_EN(0b1100), DEBOUNCE_DT(0b000) | DEBOUNCE_DR(0b000), ESI(0) | SFI(0b00), FFI(0b00) | CDC(0b111111));
  mpr121_set_threshold(MPR121_ADDRESS, 0, 0);

  DDRD |= (1 << PD2);
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

  gesture_add_trace(gesture2, 6);

  gesture_add_trace(gesture3, 11);
  gesture_add_trace(gesture3, 10);
  gesture_add_trace(gesture3, 6);
  gesture_add_trace(gesture3, 5);
  gesture_add_trace(gesture3, 1);
}