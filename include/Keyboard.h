#ifndef KEYBOARD_H
#define KEYBOARD_H

#define COLINIT 8
#define ROWINIT 12

#define NROWS 4
#define NCOLUMNS 4

void InitKeyboard(const int*, const int*);
const char (*KeyMap())[NCOLUMNS];
char ReadMap(const char (*)[NCOLUMNS], const int*, const int*);

#endif