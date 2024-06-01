#include <Arduino.h>
#include "board.h"
#include "gyro.h"

void setup()
{
    Serial.begin(115200);
    board_init();
}
void loop()
{
    gyro_update();
    gyro_data_structure_t gyro = gyro_get_data();
    Serial.printf("data:%.2f %0.2f, %f %f %f\n", gyro.angle_pitch, gyro.angle_roll, gyro.acc_x, gyro.acc_y, gyro.acc_z);
    delay(10);
}