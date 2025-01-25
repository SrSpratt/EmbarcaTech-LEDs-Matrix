#include <LEDsELM.h>
#include <GeneralPinELM.h>
#include <math.h>
#include <stdio.h>

void PrintRGB(RGB color){
    printf("---RGB---\n");
    printf("Red: %lf\n", color.Red);
    printf("Green: %lf\n", color.Green);
    printf("Blue: %lf\n", color.Blue);
    printf("---------\n");
}

void PrintPIO(refs pio){
    printf("---PIO refs---\n");
    printf("PIO Addr: %d\n", pio.Ref);
    printf("Offset inst: %d\n", pio.Offset);
    printf("State Machine no: %d\n", pio.StateMachine);
    printf("FIFO empty: %d\n", pio_sm_is_rx_fifo_empty(pio.Ref, pio.StateMachine));
    printf("FIFO full: %d\n", pio_sm_is_rx_fifo_full(pio.Ref, pio.StateMachine));
    printf("---------\n");
}

double* Drawing(int frame){
    static double firstArray[] = {
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0
    };

    static double secondArray[] = {
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0
    };

    static double thirdArray[] = {
        1.0, 0.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        1.0, 0.0, 0.0, 0.0, 1.0
    };

    static double defaultArray[] = {
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0
    };

    switch (frame){
        case 1:
            return firstArray;
            break;
        case 2:
            return secondArray;
            break;
        case 3:
            return thirdArray;
            break;
        default:
            return defaultArray;
    }
}

uint32_t RGBMatrix(RGB color){
    unsigned char R, G, B;
    R = color.Red * 255;
    G = color.Green * 255;
    B = color.Blue * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

void PrintBinary(int num) {
    printf("\n");
    int i;
    for (i = 31; i >= 0; i--) {
    (num & (1 << i)) ? printf("1") : printf("0");
    }
    printf("\n");
}

void Draw(double* drawing, uint32_t led, refs pio, RGB color){
//    PrintPIO(pio);
//    PrintRGB(color);

    for (int16_t i = 0; i < NPIXELS; i++){
        //printf("Elemento %d\n", i);
    
        if (drawing[i]){
            color.Red = 0.0;
            color.Green = drawing[i];
            color.Blue = 0.0;
        } else {
            color.Red = 1.0;
            color.Green = 1.0;
            color.Blue = 1.0;
        }
        led = RGBMatrix(color);
        pio_sm_put_blocking(pio.Ref, pio.StateMachine, led);
        //printf("LED %d: %d\n", i, led);
        // PrintRGB(color);
        // printf("LED: %d\n", led);
        // PrintPIO(pio);
        // PrintBinary(led);
        // printf("LED %d: %d\nR: %d, G: %d, B: %d\n ", i, led, color.Red, color.Green, color.Blue);
    }

}

void DrawFrames(double* drawing, uint32_t led, refs pio, RGB color, int delay){
    drawing = Drawing(1);
    Draw(drawing, led, pio, color);
    sleep_ms(delay);
    drawing = Drawing(2);
    Draw(drawing, led, pio, color);
    sleep_ms(delay);
    drawing = Drawing(3);
    Draw(drawing, led, pio, color);
    sleep_ms(delay);
    drawing = Drawing(2);
    Draw(drawing, led, pio, color);
    sleep_ms(delay);
    drawing = Drawing(1);
    Draw(drawing, led, pio, color);
    sleep_ms(delay);
    drawing = Drawing(0);
}