#include<GeneralPinELM.h>
#include "pico/stdlib.h"

void SetInput(int PIN){
    gpio_init(PIN);
    gpio_set_dir(PIN, false);
    gpio_pull_down(PIN);
}

void SetOutput(int PIN){
    gpio_init(PIN);
    gpio_set_dir(PIN, true);
    gpio_put(PIN, 0);
}