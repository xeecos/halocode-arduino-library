#include "touch.h"
#include <Arduino.h>
void touch_init_t()
{
    pinMode(2, INPUT);
    pinMode(15, INPUT);
    pinMode(32, INPUT);
    pinMode(33, INPUT);
}
int touch_status(int key)
{
    switch(key)
    {
        case 0:
            return touchRead(2);
        case 1:
            return touchRead(15);
        case 2:
            return touchRead(33);
        case 3:
            return touchRead(32);
    }
    return -1;
}