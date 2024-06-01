#include <Arduino.h>
#include "board.h"
#include "touch.h"

void setup()
{
    Serial.begin(115200);
    board_init();
}
void loop()
{
    delay(10);
    Serial.printf("touch:%d %d %d %d\n", touch_status(0), touch_status(1), touch_status(2), touch_status(3));
}