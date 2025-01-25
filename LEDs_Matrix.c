#include <stdio.h>
#include "pico/stdlib.h"
#include <KeyBoardELM.h>
#include <GeneralPinELM.h>
#include <LEDsELM.h>
#include "hardware/clocks.h"

int main()
{
    // printf("COMEÇOU\n");
    const int ROWS[NROWS] = {ROWINIT + 3, ROWINIT + 2, ROWINIT + 1, ROWINIT};
    const int COLUMNS[NCOLUMNS] = {COLINIT + 3, COLINIT + 2, COLINIT + 1, COLINIT};
    const char(*KEYMAP)[NCOLUMNS];

    refs pio;

    double *drawing = Drawing(0);

    // printf("ANTES DE INICIAR\n");
    pio = InitPIO();
    PrintPIO(pio);

    // printf("Programa iniciado!\n");
    // printf("Desenho iniciado: \n");
    // for (int i = 0; i < NPIXELS; i++)
    //     printf("%lf ", drawing[i]);

    InitKeyboard(ROWS, COLUMNS);
    // printf("DEPOIS DE INICIAR\n");

    KEYMAP = KeyMap();

    char key;
    uint32_t led = 0;
    RGB color[2] = {
        {.Red = 0.0, .Green = 0.0, .Blue = 0.0}, 
        {.Red = 1.0, .Green = 1.0, .Blue = 1.0}};

    PrintRGB(color[1]);

    int position[2] = {0,0};

    while (true)
    {
        key = ReadMap(KEYMAP, ROWS, COLUMNS);
        if (key == '1')
        {
            position[0] = 1;
            position[1] = 3;
            DrawFrames(drawing, led, pio, color, 800, position);
        }
        else if (key == '3')
        {
            color[0].Red = 0.3;
            color[0].Blue = 0.9;
            color[0].Green = 0.3;
    
            position[0] = 15;
            position[1] = 20;
            DrawFrames(drawing, led, pio, color, 800, position);
        }
        else if (key == '4')
        {
            color[0].Red = 0.9;
            color[0].Blue = 0.5;
            color[0].Green = 0.6;
    
            position[0] = 10;
            position[1] = 14;
            DrawFrames(drawing, led, pio, color, 800, position);
        }
        else if (key == '5')
        {
            color[0].Red = 0.5;
            color[0].Blue = 0.7;
            color[0].Green = 0.3;
    
            position[0] = 4;
            position[1] = 9;
            DrawFrames(drawing, led, pio, color, 800, position);
        }
        else
            Draw(drawing, led, pio, color);
        sleep_ms(100);
    }

    return 0;
}


