#include "battery_indic.h"
#include "mpr121.h"
#include "ssd1306.h"
#include "gesture.h"
#include "draw.h"
#include "system_time.h"
#include <util/delay.h>

#define MPR121_ADDRESS 0x5A

void display_pads(uint16_t pressed_pads);
void display_data(uint16_t* baseline);
void display_trace(Gesture_Observer* observer);
void reset_observer(Gesture_Observer* observer);

int main(void)
{
  i2c_init();
  init_system_tick();
  setup_battery_indic();
  mpr121_setup(MPR121_ADDRESS, ELE_EN(0b1100), DEBOUNCE_DT(0b000) | DEBOUNCE_DR(0b000), ESI(0) | SFI(0b00), FFI(0b00) | CDC(0b111111));
  mpr121_set_threshold(MPR121_ADDRESS, 0, 0);
  oled_init();
  oled_clear();

  Gesture_Observer observer = observer_create();
  Gesture gesture1 = gesture_create(1);

  gesture_add_trace(&gesture1, 9);
  gesture_add_trace(&gesture1, 5);
  gesture_add_trace(&gesture1, 1);
  gesture_add_trace(&gesture1, 2);
  gesture_add_trace(&gesture1, 3);
  gesture_add_trace(&gesture1, 7);
  gesture_add_trace(&gesture1, 11);
  gesture_add_trace(&gesture1, 10);
  gesture_add_trace(&gesture1, 9);

  observer_add_gesture(&observer, gesture1);

  uint16_t pressed_pads = 0;
  uint16_t newly_pressed = 0;
  uint16_t prev_pressed_pads = 0;
  uint16_t baselines[12];

  uint8_t observer_result = 0;

  tTime timeout = 250 * TIMER1_MILLISECOND;
  tTime last_press = 0;

  mpr121_get_filtered_baseline(MPR121_ADDRESS, baselines);

  while(1)
  {
    mpr121_get_filtered_pressed(MPR121_ADDRESS, baselines, &pressed_pads);
    newly_pressed = mpr121_get_specific_pressed(pressed_pads);

    if(time_passed(last_press) > timeout)
    {
      reset_observer(&observer);
      last_press = timer1_get_time();
    }
    
    if(newly_pressed == -1)
    {
      // do nothing
    }
    else
    {
      last_press = timer1_get_time();

      if(prev_pressed_pads != pressed_pads)
      {
        // New Button has been Pressed
        observer_inform(&observer, newly_pressed);
        oled_set_cursor(0,0);
        display_trace(&observer);
        observer_result = observer_get_result(&observer);
        
        if(observer_result)
        {
          oled_set_cursor(0,5);
          oled_write_int(observer_result);
          oled_set_cursor(0,6);
          oled_write_str("Richtig");
          delay_ms(250);
          reset_observer(&observer);
        }
      }
      prev_pressed_pads = pressed_pads;
    }
  }
}

void reset_observer(Gesture_Observer* observer)
{
  oled_clear();
  observer_clear_trace(observer);
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

void display_pads(uint16_t pressed_pads)
{
  for(uint8_t i = 0; i < 12; i++)
  {
    oled_set_cursor((i%4 * 20), i/4);

    if(pressed_pads & (1 << i))
    {
      oled_write_char('o');
    }
    else
    {
      oled_write_char('x');
    }
  }
}

void display_data(uint16_t* baseline)
{
  //oled_clear();
  for(uint8_t i = 0; i < 12; i++)
  {
    oled_set_cursor((i%3 * 30), (i/3)*2);

    oled_write_int(baseline[i]);
  }
}