#ifndef LEDSELM_H
#define LEDSELM_H

#include "GeneralPinELM.h"

#define NPIXELS 25

void PrintRGB(RGB);
const double* Drawing();
void Draw(const double*, uint32_t, refs, RGB);

#endif