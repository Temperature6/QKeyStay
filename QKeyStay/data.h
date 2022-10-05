#ifndef DATA_H
#define DATA_H

#include <qt_windows.h>

enum BUTTON
{
    Null = 0,
    LEFT,
    RIGHT,
    MID
};

enum TYPE
{
    NOTYPE = 0,
    MOUSE,
    KEYBOARD
};

extern DWORD    key;
extern bool     pressed;
extern bool     stop;
extern int      run_type;
extern int      mouse_button;

#endif // DATA_H
