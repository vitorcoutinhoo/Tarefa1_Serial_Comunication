#include "led_matrix.h"

const uint8_t NLED = 25;
PIO pio = pio0;
uint sm = 0;

// numeros a serem mostrados na matriz
uint32_t numbers[10][25] = {
    {0, 1, 1, 1, 0,  0, 1, 0, 1, 0,  0, 1, 0, 1, 0,  0, 1, 0, 1, 0,  0, 1, 1, 1, 0}, // 0
    {0, 1, 1, 1, 0,  0, 0, 1, 0, 0,  0, 0, 1, 0, 0,  0, 1, 1, 0, 0,  0, 0, 1, 0, 0}, // 1
    {0, 1, 1, 1, 0,  0, 1, 0, 0, 0,  0, 1, 1, 0, 0,  0, 0, 0, 1, 0,  0, 1, 1, 1, 0}, // 2
    {0, 1, 1, 1, 0,  0, 0, 0, 1, 0,  0, 1, 1, 1, 0,  0, 0, 0, 1, 0,  0, 1, 1, 1, 0}, // 3
    {0, 1, 0, 0, 0,  0, 0, 0, 1, 0,  0, 1, 1, 1, 0,  0, 1, 0, 1, 0,  0, 1, 0, 1, 0}, // 4
    {0, 1, 1, 1, 0,  0, 0, 0, 1, 0,  0, 0, 1, 1, 0,  0, 1, 0, 0, 0,  0, 1, 1, 1, 0}, // 5
    {0, 1, 1, 1, 0,  0, 1, 0, 1, 0,  0, 1, 1, 1, 0,  0, 1, 0, 0, 0,  0, 1, 1, 0, 0}, // 6
    {0, 0, 1, 0, 0,  0, 0, 1, 0, 0,  0, 0, 1, 0, 0,  0, 0, 0, 1, 0,  0, 1, 1, 1, 0}, // 7
    {0, 1, 1, 1, 0,  0, 1, 0, 1, 0,  0, 1, 1, 1, 0,  0, 1, 0, 1, 0,  0, 1, 1, 1, 0}, // 8
    {0, 0, 1, 1, 0,  0, 0, 0, 1, 0,  0, 1, 1, 1, 0,  0, 1, 0, 1, 0,  0, 1, 1, 1, 0}  // 9
};

// Função para colocar a cor do LED na matriz
void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb);
}

// Função para representar a cor em formato RGB
uint32_t color(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)(g) << 24) | ((uint32_t)(r) << 16) | ((uint32_t)(b) << 8);
}

// Função para mostrar um numero na matriz de led
void display_number(uint8_t number, uint32_t color) {
    for (uint i = 0; i < NLED; i++) {
        if (numbers[number][i]) put_pixel(color);
        else put_pixel(0);
    }
}