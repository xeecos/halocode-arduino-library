#include <Arduino.h>
#include "led_matrix.h"

void setup()
{
    led_matrix_init_t();
}
float j, f, k;
void loop()
{
    for(uint8_t i = 0; i < 12; i++)
    {
        uint8_t red	= 32 * (1 + sin(i / 2.0 + j / 4.0) );
        uint8_t green = 32 * (1 + sin(i / 1.0 + f / 9.0 + 2.1) );
        uint8_t blue = 32 * (1 + sin(i / 3.0 + k / 14.0 + 4.2) );
        led_matrix_set_single_led_t(i, red, green, blue);
    }
    j += random(1, 6) / 6.0;
    f += random(1, 6) / 6.0;
    k += random(1, 6) / 6.0;
    led_matrix_update_t();
    delay(40);
}