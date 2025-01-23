#include <stdio.h>
#include "pico/stdlib.h"
#include <HelloWorld.h>



int main()
{
    stdio_init_all();
    HelloWorld();
    /*
    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }*/
    return 0;
}
