#include <stdio.h>
#include "pico/stdlib.h"
#include "AnimacaoCruz.h"
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

//arquivo .pio
#include "pio_matrix.pio.h"

const uint8_t rowPins[] = {15, 14, 13, 12};  // Linhas do teclado
const uint8_t colsPins[] = {11, 10, 9, 8};  // Colunas do teclado

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

// Captura do que foi apertado no teclado
char ReadKeypad() {
    for (int j = 0; j < 4; j++) {
        gpio_put(colsPins[j], 1);
        for (int i = 0; i < 4; i++) {
            if (gpio_get(rowPins[i])) {
                char key = keypad[i][j];
                sleep_ms(200);  // Debounce
                while (gpio_get(rowPins[i]));
                gpio_put(colsPins[j], 0);
                return key;
            }
        }
        gpio_put(colsPins[j], 0);
    }
    return '\0';
}

void ProcessKey(char key) {

}

//Número de LEDs
#define numPixels 25

//Pino de saída
#define pinoLed 7

//Vetor para criar imagem na matriz de led
double desenho[25] =   {0.0, 0.3, 0.3, 0.3, 0.0,
                        0.0, 0.3, 0.0, 0.3, 0.0, 
                        0.0, 0.3, 0.3, 0.3, 0.0,
                        0.0, 0.3, 0.0, 0.3, 0.0,
                        0.0, 0.3, 0.3, 0.3, 0.0};

//Vetor para criar imagem na matriz de led
double desenhoAnimacao[25] =   {0.5, 0.1, 0.3, 0.2, 0.0,
                                0.0, 0.3, 0.0, 0.7, 0.0, 
                                0.0, 0.8, 0.7, 0.3, 0.0,
                                0.5, 0.2, 0.0, 0.9, 0.0,
                                0.0, 0.3, 0.1, 0.3, 0.5};


//Rotina para definição da intensidade de cores do led
uint32_t MatrixRGB(double b, double r, double g) {
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

//Rotina para acionar a matrix de leds - ws2812b
void desenhoPIO(double *desenho, uint32_t valorLed, PIO pio, uint sm, double r, double g, double b){

    for (int16_t i = 0; i < numPixels; i++) {
        if (i%2==0)
        {
            valorLed = MatrixRGB(desenho[24-i], r=0.0, g=0.0);
            pio_sm_put_blocking(pio, sm, valorLed);

        }else{
            valorLed = MatrixRGB(b=0.0, desenho[24-i], g=0.0);
            pio_sm_put_blocking(pio, sm, valorLed);
        }
    }
}

int AnimacaoCruz(){
    PIO pio = pio0; 
    bool ok;
    uint16_t i;
    uint32_t valor_led;
    double r = 0.0, b = 0.0 , g = 0.0;

    //coloca a frequência de clock para 128 MHz, facilitando a divisão pelo clock
    ok = set_sys_clock_khz(128000, false);

    // Inicializa todos os códigos stdio padrão que estão ligados ao binário.
    stdio_init_all();

    //configurações da PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, pinoLed);

    InitializeKeypad();

    while (1){
        char key = ReadKeypad();
        //ProcessKey(key);

            if (key != '\0') {
                printf("Tecla apertada: %c\n", key);
                if (key == '8'){
                    desenhoPIO(desenhoAnimacao, valor_led, pio, sm, r, g, b);
                }
            } else{
                //rotina para escrever na matriz de leds com o emprego de PIO - desenho inicial
                desenhoPIO(desenho, valor_led, pio, sm, r, g, b);
            }

        sleep_ms(500);
    }
    
}


