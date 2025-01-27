#include <LEDsELM.h>
#include <GeneralPinELM.h>
#include <math.h>
#include <stdio.h>

void PrintRGB(RGB color)
{
    printf("---RGB---\n");
    printf("Red: %lf\n", color.Red);
    printf("Green: %lf\n", color.Green);
    printf("Blue: %lf\n", color.Blue);
    printf("---------\n");
}

void PrintPIO(refs pio)
{
    printf("---PIO refs---\n");
    printf("PIO Addr: %d\n", pio.Ref);
    printf("Offset inst: %d\n", pio.Offset);
    printf("State Machine no: %d\n", pio.StateMachine);
    printf("FIFO empty: %d\n", pio_sm_is_rx_fifo_empty(pio.Ref, pio.StateMachine));
    printf("FIFO full: %d\n", pio_sm_is_rx_fifo_full(pio.Ref, pio.StateMachine));
    printf("---------\n");
}

double *Drawing(int frame)
{
    //Desenho X
    static double firstFrameX[] = {
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0};

    static double secondFrameX[] = {
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0};

    static double thirdFrameX[] = {
        1.0, 0.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        1.0, 0.0, 0.0, 0.0, 1.0};

    //Desenho da Cuz
    static double firstFrameCruz[] = {
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0};

    // Frame 1: Estrela na parte superior
    static double frame1[] = {
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0};

    // Frame 2: Estrela no centro
    static double frame2[] = {
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0};

    // Frame 3: Estrela na parte inferior
    static double frame3[] = {
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};
    //Desenho padrão
    static double defaultArray[] = {
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0};

    switch (frame)
    {
    case 1:
        return firstFrameX;
        break;
    case 2:
        return secondFrameX;
        break;
    case 3:
        return thirdFrameX;
        break;
    case 4:
        return firstFrameCruz;
        break;
    case 5:
        return frame1; // Primeiro frame da estrela
    case 6:
        return frame2; // Segundo frame da estrela
    case 7:
        return frame3; // Terceiro frame da estrela
    default:
        return defaultArray;
    }
}

uint32_t RGBMatrix(RGB color)
{
    unsigned char R, G, B;
    R = color.Red * 255;
    G = color.Green * 255;
    B = color.Blue * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

void PrintBinary(int num)
{
    printf("\n");
    int i;
    for (i = 31; i >= 0; i--)
    {
        (num & (1 << i)) ? printf("1") : printf("0");
    }
    printf("\n");
}

void Draw(double *drawing, uint32_t led, refs pio, RGB *color)
{
    //    PrintPIO(pio);
    //    PrintRGB(color);
    RGB finalColor;

    for (int16_t i = 0; i < NPIXELS; i++)
    {
        // printf("Elemento %d\n", i);

        if (drawing[i])
        {
            finalColor.Red = color[0].Red;
            finalColor.Green = color[0].Green;
            finalColor.Blue = color[0].Blue;
        }
        else
        {
            finalColor.Red = color[1].Red;
            finalColor.Green = color[1].Green;
            finalColor.Blue = color[1].Blue;
        }
        led = RGBMatrix(finalColor);
        pio_sm_put_blocking(pio.Ref, pio.StateMachine, led);
        // printf("LED %d: %d\n", i, led);
        //  PrintRGB(color);
        //  printf("LED: %d\n", led);
        //  PrintPIO(pio);
        //  PrintBinary(led);
        //  printf("LED %d: %d\nR: %d, G: %d, B: %d\n ", i, led, color.Red, color.Green, color.Blue);
    }
}

void DrawFrames(double *drawing, uint32_t led, refs pio, RGB *color, int delay, int *position)
{
    drawing = Drawing(0);
    Draw(drawing, led, pio, color);
    sleep_ms(delay);

    for (int i = position[0]; i <= position[1]; i++)
    {
        drawing = Drawing(i);
        Draw(drawing, led, pio, color);
        sleep_ms(delay);
    }

    for (int i = position[1]; i >= position[0]; i--)
    {
        drawing = Drawing(i);
        Draw(drawing, led, pio, color);
        sleep_ms(delay);
    }
}

void AnimateMovingStar(uint32_t led, refs pio, RGB *color)
{
    int delay = 300; // Tempo entre frames (em milissegundos)
    int position[] = {5, 7}; // Frames da animação (de frame1 a frame3)

    // Desenha os frames em ordem (movimento para baixo)
    for (int i = position[0]; i <= position[1]; i++)
    {
        Draw(Drawing(i), led, pio, color);
        sleep_ms(delay);
    }

    // Desenha os frames em ordem reversa (movimento para cima)
    for (int i = position[1]; i >= position[0]; i--)
    {
        Draw(Drawing(i), led, pio, color);
        sleep_ms(delay);
    }
}
