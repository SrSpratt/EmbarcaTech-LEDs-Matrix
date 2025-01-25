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
    printf("---------\n");
}

const double* Drawing(){
    static const double array[] = {
        1.0, 0.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        1.0, 0.0, 0.0, 0.0, 1.0
    };
    return array;
}

uint32_t RGBMatrix(RGB color){
    unsigned char R, G, B;
    R = color.Red * 255;
    G = color.Green * 255;
    B = color.Blue * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

void Draw(const double* drawing, uint32_t led, refs pio, RGB color){
    PrintPIO(pio);
    PrintRGB(color);

    for (int16_t i = 0; i < NPIXELS; i++){
        printf("Elemento %d\n", i);
        if((i%2) == 0){
            color.Red = 0.0;
            color.Green = 0.0;
            color.Blue = drawing[NPIXELS-1-i];
            //printf("%d\n",24-i);
            //printf("%lf\n",drawing[24-i]);
            led = RGBMatrix(color);
        } else {
            color.Red = drawing[NPIXELS-1-i];
            color.Green = 0.0;
            color.Blue = 0.0;
            led = RGBMatrix(color);
        }
        pio_sm_put_blocking(pio.Ref, pio.StateMachine, led);
        //printf("LED %d: %d\n", i, led);
        PrintRGB(color);
        printf("LED: %d\n", led);
        // printf("LED %d: %d\nR: %d, G: %d, B: %d\n ", i, led, color.Red, color.Green, color.Blue);
    }

}
