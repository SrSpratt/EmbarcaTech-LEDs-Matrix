#include <stdio.h>
#include "pico/stdlib.h"
#include <KeyBoardELM.h>


int main()
{
    //printf("COMEÇOU\n");
    const int ROWS[NROWS] = {ROWINIT + 3, ROWINIT + 2, ROWINIT + 1, ROWINIT};
    const int COLUMNS[NCOLUMNS] = {COLINIT + 3, COLINIT + 2, COLINIT + 1, COLINIT};
    const char (*KEYMAP)[NCOLUMNS];

    //printf("ANTES DE INICIAR\n");
    stdio_init_all();
    InitKeyboard(ROWS, COLUMNS);
    //printf("DEPOIS DE INICIAR\n");

    KEYMAP = KeyMap();

    char key;
    while(true){
        key = ReadMap(KEYMAP, ROWS, COLUMNS);
        if (key != '$')
            printf("Caractere pressionado: %c\n", key);
        sleep_ms(100);
    }
    
    return 0;
}
