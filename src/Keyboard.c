#include <KeyboardELM.h>
#include <GeneralPinELM.h>
#include "pico/stdlib.h"

void InitKeyboard(const int* ROWS, const int* COLUMNS){

    for(int i = 0; i < NROWS; i++){
        SetInput(ROWS[i]);
        //printf("Pin initiated: %d\n", ROWS[i]);
    }

    for(int i = 0; i < NCOLUMNS; i++){
        SetOutput(COLUMNS[i]);
        //printf("Pin initiated: %d\n", COLUMNS[i]);
    }

}

const char (*KeyMap())[NCOLUMNS]{

    const static char KEYMAP[4][4] = {
        {'1','2','3', 'A'},
        {'4','5','6', 'B'},
        {'7','8','9', 'C'},
        {'*','0','#', 'D'},
    };

    return KEYMAP;
}

char ReadMap(const char (*KEYMAP)[NCOLUMNS], const int* ROWS, const int* COLUMNS){
    for(int col = 0; col < NCOLUMNS; col++){
        gpio_put(COLUMNS[col], 1);

        for(int row = 0; row < NROWS; row++){
            if (gpio_get(ROWS[row])){
                gpio_put(COLUMNS[col], 0);
                //printf("AQUI");
                return KEYMAP[row][col];
            }
        }
        gpio_put(COLUMNS[col], 0);
    }
    return '$';
}
// adicionada aperta 3
void HandleKeyPress(const char key, const int* led, PIO pio, const int* colors) {
    if (key == '3') { // Tecla 3 para a animação da estrela
        AnimateMovingStar(led, pio, colors); // Chama a animação
    }
}
