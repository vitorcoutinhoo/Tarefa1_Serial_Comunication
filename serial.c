#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "ws2812.pio.h"
#include "led_matrix.h"

// Definição dos pinos
#define GREEN_LED 11
#define BLUE_LED 12
#define BUTTOM_A 5
#define BUTTOM_B 6
#define MATRIX 7

// Constante para debouncing
uint32_t volatile last_time = 0;

// Constante para o numero na matriz de led
uint8_t volatile number = 0;


// Inicia e seta a direção do pino 
void init_gpio(uint8_t gpio, uint8_t dir) {
    gpio_init(gpio);
    gpio_set_dir(gpio, dir);
}

// Função de interrupção
void led_handler(uint8_t gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    // Debouncing de 250ms
    if (current_time - last_time > 250000) {
        last_time = current_time;

        // Alterna o led verde
        if(gpio == BUTTOM_A) {
            gpio_put(GREEN_LED, !gpio_get(GREEN_LED));
            printf("Alternando led Verde!\n");
        }

        // Alterna o led azul
        if(gpio == BUTTOM_B) {
            gpio_put(BLUE_LED, !gpio_get(BLUE_LED));
            printf("Alternando led Azul!\n");
        }
    }

}

int main() {
    stdio_init_all();

    init_gpio(GREEN_LED, GPIO_OUT);
    init_gpio(BLUE_LED, GPIO_OUT);

    init_gpio(BUTTOM_A, GPIO_IN);
    init_gpio(BUTTOM_B, GPIO_IN);

    gpio_pull_up(BUTTOM_A);
    gpio_pull_up(BUTTOM_B);

    // Configura a máquina de estados PIO para começar a controlar os LEDs WS2812.
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, MATRIX, 800000, false);

    // Seta a função de callback quando os botões a e b forem pressionados
    gpio_set_irq_enabled_with_callback(BUTTOM_A, GPIO_IRQ_EDGE_FALL, true, &led_handler);
    gpio_set_irq_enabled_with_callback(BUTTOM_B, GPIO_IRQ_EDGE_FALL, true, &led_handler);

    while (true) {
        for (int i = 0; i < NLED; i++)
            put_pixel(color(5, 5, 5));
        sleep_ms(1000);
    }
}
