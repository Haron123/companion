#include "draw.h"

static inline int8_t canvas_check_draw(uint8_t x, uint8_t y)
{
  if(x >= CANVAS_WIDTH || (y >= CANVAS_HEIGHT * 8))
  {
    return -1;
  }

  return 0;
}

Canvas canvas_create()
{
  Canvas temp;

  for(uint16_t i = 0; i < CANVAS_HEIGHT*CANVAS_WIDTH; i++)
  { 
    temp.canvas_buffer[i/128][i%128] = 0x00;
  }

  return temp;
}

void canvas_draw(Canvas* canvas, uint8_t x, uint8_t y, uint8_t delete)
{
  if(canvas_check_draw(x, y) == 0)
  {
    if(delete)
    {
      canvas->canvas_buffer[y / CANVAS_HEIGHT][x] &= ~(1 << (y % CANVAS_HEIGHT));
    }
    else
    {
      canvas->canvas_buffer[y / CANVAS_HEIGHT][x] |= (1 << (y % CANVAS_HEIGHT));
    }
    
  } 
}

void canvas_update(Canvas* canvas)
{
  oled_set_cursor(0,0);
  for(uint16_t i = 0; i < CANVAS_HEIGHT*CANVAS_WIDTH; i++)
  { 
    oled_write_byte(canvas->canvas_buffer[i/128][i%128]);
  }
}