#include "button.h"
#include <Arduino.h>

void button_init_t()
{
    pinMode(26, INPUT);
}
int button_status()
{
    return digitalRead(26);
}