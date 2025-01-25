#include <Keyboard.h>
#include "pico/stdlib.h"

void InitKeyboard(const int* ROWS, const int* COLUMNS){

    for(int i = 0; i < NROWS; i++){
        gpio_init(ROWS[i]);
        gpio_set_dir(ROWS[i], false);
        gpio_pull_down(ROWS[i]);
        //printf("Pin initiated: %d\n", ROWS[i]);
    }

    for(int i = 0; i < NCOLUMNS; i++){
        gpio_init(COLUMNS[i]);
        gpio_set_dir(COLUMNS[i], true);
        gpio_put(COLUMNS[i], 0);
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