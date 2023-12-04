#ifndef SERIAL_H
#define SERIAL_H

void uart_init(void);

void uart_putchar(char c);

char uart_getchar(void);

#endif