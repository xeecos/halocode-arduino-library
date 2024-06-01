#include "board.h"
#include "i2c_master.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "driver/i2s.h"
#include "led_matrix.h"
#include "gyro.h"
#include "button.h"
#include "touch.h"
#include "microphone.h"

#define I2C_NUM (I2C_NUM_1)
#define I2C_FREQUENCY (100000)
void _board_thread(void* params)
{
    size_t bytes_read = 0;
    int mic_length = 1024;
    uint8_t *samples = (uint8_t*)malloc(1024);
    while(1)
    {
        i2s_read(I2S_NUM_1, samples, mic_length, &bytes_read, portMAX_DELAY);
        int32_t dac_value = 0;
        int32_t dac_value_addition = 0;
        int16_t maximum_value = 0;
        for(int i = 0; i < mic_length; i += 16)
        {
            val2byte.byteVal[1] = samples[i + 1];
            val2byte.byteVal[0] = samples[i + 0];
            dac_value = val2byte.shortVal;
            dac_value_addition = dac_value_addition + abs(dac_value);
            if(abs(dac_value) > maximum_value)
            {
                maximum_value = abs(dac_value);
            }
        }
        microphone_update_t(16 * dac_value_addition / mic_length);
    }
}
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
    microphone_init_t();

    TaskHandle_t _threadTask;
    xTaskCreatePinnedToCore(_board_thread, "_board_thread", 10000, NULL, 8, &_threadTask, 1);
}