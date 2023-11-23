#ifndef DRAW_H
#define DRAW_H

#include "ssd1306.h"

#define CANVAS_HEIGHT 8
#define CANVAS_WIDTH 128

typedef struct Canvas
{
  uint8_t canvas_buffer[CANVAS_HEIGHT][CANVAS_WIDTH];
} Canvas;

/**
 * @brief sets the canvas buffer to zero
 * @retval a correctly initialized canvas
*/
Canvas canvas_create();

/**
 * @brief draws a single spot inside of the canvas
 * @param x the x coordinate of the spot
 * @param y the y coordinate of the spot
 * @param delete if set to one, will erase the spot instead of drawing it
*/
void canvas_draw(Canvas* canvas, uint8_t x, uint8_t y, uint8_t delete);

/**
 * @brief draws the contents of the canvas to the display
*/
void canvas_update(Canvas* canvas);

#endif