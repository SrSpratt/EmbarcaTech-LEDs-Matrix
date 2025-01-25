#include <stdio.h>
#include "pico/stdlib.h"
#include <KeyBoardELM.h>
#include <GeneralPinELM.h>
#include <LEDsELM.h>
#include "hardware/clocks.h"


int main()
{
    //printf("COMEÇOU\n");
    const int ROWS[NROWS] = {ROWINIT + 3, ROWINIT + 2, ROWINIT + 1, ROWINIT};
    const int COLUMNS[NCOLUMNS] = {COLINIT + 3, COLINIT + 2, COLINIT + 1, COLINIT};
    const char (*KEYMAP)[NCOLUMNS];

    refs pio;

    double* drawing = Drawing(0);

    //printf("ANTES DE INICIAR\n");
    pio = InitPIO();
    PrintPIO(pio);

    // printf("Programa iniciado!\n");
    // printf("Desenho iniciado: \n");
    // for (int i = 0; i < NPIXELS; i++)
    //     printf("%lf ", drawing[i]);

    InitKeyboard(ROWS, COLUMNS);
    //printf("DEPOIS DE INICIAR\n");

    KEYMAP = KeyMap();

    char key;
    uint32_t led = 0;
    RGB color = { .Red = 0.0, .Green = 0.0, .Blue = 0.0 };
    PrintRGB(color);

    while(true){
        key = ReadMap(KEYMAP, ROWS, COLUMNS);
        if (key == '1'){
            DrawFrames(drawing, led, pio, color, 1500);
        }
        else
            Draw(drawing, led, pio, color);
        sleep_ms(100);
    }
    
    return 0;
}
