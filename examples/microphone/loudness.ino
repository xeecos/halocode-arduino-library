#include <Arduino.h>
#include "board.h"
#include "microphone.h"

void setup()
{
    Serial.begin(115200);
    board_init();
}
void loop()
{
    Serial.printf("loudness:%d\n", microphone_loudness());
    delay(10);
}