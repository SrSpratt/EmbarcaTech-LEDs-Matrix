#include <stdio.h>
#include "pico/stdlib.h"
#include <HelloWorld.h>
#include "AnimacaoCruz.h"


int main()
{
    //stdio_init_all();
    HelloWorld();
    /*
    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }*/
    /*
    InitializeKeypad();
    
    while (true) {
        char key = ReadKeypad();
        ProcessKey(key);
    }*/

    AnimacaoCruz();
    return 0;
}
