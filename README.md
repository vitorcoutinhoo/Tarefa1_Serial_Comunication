## Tarefa 1 - Comunicação serial

### Descrição

Este projeto tem como objetivo controlar LEDs, uma matriz de LEDs WS2812 e um display OLED SSD1306 via protocolo I2C. Ele permite alternar os LEDs ao pressionar botões, exibir mensagens no display e mostrar números na matriz de LEDs.

### Dependências

Para compilar e rodar este projeto, é necessário ter:

- Raspberry Pi Pico SDK

- Biblioteca ssd1306.h para controle do display OLED

- Biblioteca ws2812.pio.h para controle da matriz de LEDs WS2812

- Biblioteca led_matrix.h para funções da matriz de LEDs

Todas essas bibliotecas se encontram na pasta ```Lib```.

### Hardware Utilizado

- Raspberry Pi Pico

- Display OLED SSD1306 (I2C)

- Matriz de LEDs WS2812

- LEDs individuais (verde e azul)

- Botões de entrada (A e B)

Todos presentes na placa BitDogLab.

### Pinos Utilizados

LEDs:

- Verde: GPIO 11

- Azul: GPIO 12

Botões:

- Botão A: GPIO 5

- Botão B: GPIO 6

Matriz de LEDs: GPIO 7

Display OLED (I2C):

- SDA: GPIO 14

- SCL: GPIO 15

### Funcionalidades

- Pressionar o Botão A alterna o LED verde e exibe "Led Verde Alternado" no display OLED.

- Pressionar o Botão B alterna o LED azul e exibe "Led Azul Alternado" no display OLED.

- Ao conectar via USB, o programa recebe caracteres e os exibe no display OLED.

- Se um número de 0 a 9 for digitado, ele será mostrado na matriz de LEDs WS2812.

- O buffer do display é limitado a 48 caracteres e reseta ao atingir esse limite.

### Vídeo Demonstração

Vídeo mostrando uma breve explicação sobre o código e todas as funcionalidades na placa BitDogLab.

[Clique Aqui para assistir ao vídeo!](https://www.youtube.com/watch?v=qn0JC9xMxi4)

## Biblioteca: led_matrix.h

### Descrição

A biblioteca led_matrix.h criada para provê as funções para controle da matriz de LEDs WS2812 conectada ao Raspberry Pi Pico.

### Funções

```void put_pixel(uint32_t pixel_grb);```

- Define a cor de um LED na matriz enviando o valor para o PIO do Raspberry Pi Pico.

```uint32_t color(uint8_t r, uint8_t g, uint8_t b);```

- Gera um valor de cor no formato GRB com os valores de vermelho, verde e azul.

```void display_number(uint8_t number, uint32_t color);```

- Mostra um número na matriz de LEDs, de 0 a 9, utilizando a cor especificada.

```void display_off();```

- Apaga todos os LEDs da matriz.

### Exemplo de Uso

```c
#include "led_matrix.h"

// Mostra o número 5 na matriz em vermelho
display_number(5, color(255, 0, 0)); 
```
