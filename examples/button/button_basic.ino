#include <Arduino.h>
#include "board.h"
#include "button.h"

void setup()
{
    Serial.begin(115200);
    board_init();
}
void loop()
{
    delay(10);
    Serial.printf("key:%d\n", button_status());
}