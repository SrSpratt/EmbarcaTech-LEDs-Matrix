#include <stdio.h>
#include "pico/stdlib.h"

const uint8_t rowPins[] = {12, 13, 14, 15};  // Linhas do teclado
const uint8_t colsPins[] = {8, 9, 10, 11};  // Colunas do teclado

const char keypad[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Inicialização e direção dos pinos do teclado matricial
void InitializeKeypad() {
    for (int i = 0; i < 4; i++) {
        gpio_init(rowPins[i]);
        gpio_set_dir(rowPins[i], GPIO_IN);
        gpio_pull_down(rowPins[i]);
        gpio_init(colsPins[i]);
        gpio_set_dir(colsPins[i], GPIO_OUT);
    }
}