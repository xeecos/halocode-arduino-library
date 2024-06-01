#include "board.h"
#include "i2c_master.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "led_matrix.h"
#include "gyro.h"
#include "button.h"
#include "touch.h"

#define I2C_NUM (I2C_NUM_1)
#define I2C_FREQUENCY (100000)

void board_init()
{
    i2c_master_structure_t i2c_config;
    i2c_config.i2c_master_port = I2C_NUM_1;
    i2c_config.i2c_mode = I2C_MODE_MASTER;
    i2c_config.sda_io_num = 19;
    i2c_config.sda_pullup_en = GPIO_PULLUP_DISABLE;
    i2c_config.scl_io_num = 18;
    i2c_config.scl_pullup_en = GPIO_PULLUP_DISABLE;
    i2c_config.clk_speed = I2C_FREQUENCY;

    if (i2c_master_init_t(&i2c_config) == -1)
    {
        return;
    }
    button_init_t();
    touch_init_t();
    led_matrix_init_t();
    gyro_init_t();
    gyro_event_init_t();
}