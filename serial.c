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

// Função de interrupção
void led_handler(uint8_t gpio, uint32_t events) {

    if(gpio == BUTTOM_A) gpio_put(GREEN_LED, !gpio_get(GREEN_LED));

    if(gpio == BUTTOM_B) gpio_put(BLUE_LED, !gpio_get(BLUE_LED));
}

int main() {
    stdio_init_all();

    init_gpio(GREEN_LED, GPIO_OUT);
    init_gpio(BLUE_LED, GPIO_OUT);

    init_gpio(BUTTOM_A, GPIO_IN);
    init_gpio(BUTTOM_B, GPIO_IN);

    gpio_pull_up(BUTTOM_A);
    gpio_pull_up(BUTTOM_B);

    // Seta a função de callback quando os botões a e b forem pressionados
    gpio_set_irq_enabled_with_callback(BUTTOM_A, GPIO_IRQ_EDGE_FALL, true, &led_handler);
    gpio_set_irq_enabled_with_callback(BUTTOM_B, GPIO_IRQ_EDGE_FALL, true, &led_handler);

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
