#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "ws2812.pio.h"
#include "led_matrix.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#include "font.h"

// Definição dos pinos
#define GREEN_LED 11
#define BLUE_LED 12
#define BUTTOM_A 5
#define BUTTOM_B 6
#define MATRIX 7
#define Max 48

// Pinos do display 
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

// Constante para debouncing
uint32_t volatile last_time = 0;

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

    // Inicializa o i2c na taxa de 400khz.
    i2c_init(I2C_PORT, 400 * 1000);

    // Seta os pinos do displau pra função i2c.
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); 
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);

    // Coloca os pinos em pull-up.
    gpio_pull_up(I2C_SDA); 
    gpio_pull_up(I2C_SCL); 

    // Configura a máquina de estados PIO para começar a controlar os LEDs WS2812.
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, MATRIX, 800000, false);

    // Seta a função de callback quando os botões a e b forem pressionados.
    gpio_set_irq_enabled_with_callback(BUTTOM_A, GPIO_IRQ_EDGE_FALL, true, &led_handler);
    gpio_set_irq_enabled_with_callback(BUTTOM_B, GPIO_IRQ_EDGE_FALL, true, &led_handler);

    // Inicializa e configura o display
    ssd1306_t ssd; 
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); 
    ssd1306_config(&ssd); 
    ssd1306_send_data(&ssd);

    // Limpa o display.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);

    char buffer[Max + 1] = "";
    uint8_t count = 0;

    while (true) {

        ssd1306_fill(&ssd, false); 
        ssd1306_rect(&ssd, 0, 0, 128, 63, true, false);

        for (uint i = 0; i < count; i++){ 
            uint8_t x = 16 + (i % 12) * 8;  
            uint8_t y = 12 + (i / 12) * 10;

            ssd1306_draw_char(&ssd, buffer[i], x, y);
        }

        ssd1306_send_data(&ssd);

        if (stdio_usb_connected()) {
            char c;

            if (scanf("%c", &c) == 1) {
                if (count < Max) {
                    buffer[count++] = c;
                    buffer[count] = '\0';

                    printf("Recebido: %c\n", c);
                }
                else {
                    printf("Limite de %d caracteres atingido!\nApagando o display!\n", Max);

                    // Reseta o display
                    ssd1306_fill(&ssd, false); 
                    ssd1306_rect(&ssd, 0, 0, 128, 63, true, false);

                    count = 0;
                    buffer[count++] = c;
                    buffer[count] = '\0';
                }
            }
        }
    }
}
