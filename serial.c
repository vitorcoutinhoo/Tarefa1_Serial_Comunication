#include <stdio.h>
#include "pico/stdlib.h"

// Definição dos pinos
#define GREEN_LED 11
#define BLUE_LED 12
#define BUTTOM_A 5
#define BUTTOM_B 6

// Inicia e seta a direção do pino
void init_gpio(uint8_t gpio, uint8_t dir) {
    gpio_init(gpio);
    gpio_set_dir(gpio, dir);
}

int main() {
    stdio_init_all();

    init_gpio(GREEN_LED, GPIO_OUT);
    init_gpio(BLUE_LED, GPIO_OUT);

    init_gpio(BUTTOM_A, GPIO_IN);
    init_gpio(BUTTOM_B, GPIO_IN);

    gpio_pull_up(BUTTOM_A);
    gpio_pull_up(BUTTOM_B);

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
