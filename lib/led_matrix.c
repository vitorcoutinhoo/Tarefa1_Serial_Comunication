#include "led_matrix.h"

const uint8_t NLED = 25;
PIO pio = pio0;
uint sm = 0;

// Função para colocar a cor do LED  na matriz
void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb);
}

// Função para representar a cor em formato RGB
uint32_t color(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)(g) << 24) | ((uint32_t)(r) << 16) | ((uint32_t)(b) << 8);
}