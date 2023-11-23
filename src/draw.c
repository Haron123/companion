#include "draw.h"

static inline int8_t canvas_check_draw(Canvas* canvas, uint8_t x, uint8_t y)
{
  if(x >= CANVAS_WIDTH || y >= CANVAS_HEIGHT)
  {
    return -1;
  }

  return 0;
}

void canvas_draw(Canvas* canvas, uint8_t x, uint8_t y, uint8_t delete)
{
  if(canvas_check_draw(canvas, x, y) != -1)
  {
    canvas->canvas_buffer[y / CANVAS_HEIGHT][x] = (1 << (y % CANVAS_HEIGHT));
  } 
}

void canvas_update(Canvas* canvas)
{
  for(uint16_t i = 0; i < CANVAS_HEIGHT*CANVAS_WIDTH; i++)
  {
    oled_set_cursor(0,0);
    oled_write_byte(canvas->canvas_buffer[i/8][i%128]);
  }
}