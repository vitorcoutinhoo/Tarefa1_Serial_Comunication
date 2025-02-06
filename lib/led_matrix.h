#include "pico/stdlib.h"
#include "hardware/pio.h"

// Constantes
extern const uint8_t NLED;
extern PIO pio;
extern uint sm;

extern uint32_t numbers[10][25];

// Funções para acender o led na posição da matriz
void put_pixel(uint32_t pixel_grb);
uint32_t color(uint8_t r, uint8_t g, uint8_t b);
void display_number(uint8_t number, uint32_t color);
