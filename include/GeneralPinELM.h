#ifndef GENERALPINELM_H
#define GENERALPINELM_H

#define LEDMPIN 7
#define BUZZERPIN 21

#define COLINIT 8
#define ROWINIT 12

#define NROWS 4
#define NCOLUMNS 4

#include "hardware/pio.h"

typedef struct PIORefs {
    PIO Ref;
    uint Offset;
    uint StateMachine;
} refs;

typedef struct RGB {
    double Red;
    double Green;
    double Blue;
} RGB;

refs InitConf();
refs InitPIO();
void SetInput(int);
void SetOutput(int);

#endif