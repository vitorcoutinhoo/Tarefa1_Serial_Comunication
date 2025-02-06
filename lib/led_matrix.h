#include "pico/stdlib.h"
#include "hardware/pio.h"

// Constantes
extern const uint8_t NLED;
extern PIO pio;
extern uint sm;


void put_pixel(uint32_t pixel_grb);
uint32_t color(uint8_t r, uint8_t g, uint8_t b);
