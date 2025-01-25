#ifndef LEDSELM_H
#define LEDSELM_H

#include "GeneralPinELM.h"

#define NPIXELS 25

void PrintRGB(RGB);
void PrintPIO(refs);
double* Drawing(int);
void Draw(double*, uint32_t, refs, RGB*);
void DrawFrames(double*, uint32_t, refs, RGB*, int, int*);

#endif