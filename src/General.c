#include<GeneralPinELM.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pio_matrix.pio.h"


refs InitConf(){
    refs pio;

    pio.Ref = pio0;
    stdio_init_all();
    if (set_sys_clock_khz(128000, false))
        printf("Clock configurado para %ld\n", clock_get_hz(clk_sys));
    pio.Offset = pio_add_program(pio.Ref, &pio_matrix_program);
    pio.StateMachine = pio_claim_unused_sm(pio.Ref, true);
    
    return pio;
}

refs InitPIO(){
    refs pio = InitConf();
    pio_matrix_program_init(pio.Ref, pio.StateMachine, pio.Offset, LEDMPIN);
    return pio;
}

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