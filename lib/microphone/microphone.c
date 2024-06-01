#include "microphone.h"
#include "i2c_master.h"
#include "driver/i2c.h"
#include "driver/i2s.h"
#include "driver/dac.h"

int _loudness = 0;
void microphone_init_t()
{
    i2s_config_t i2s_config =
    {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate =  160000,
        .bits_per_sample = (i2s_bits_per_sample_t)16,
        .channel_format = (i2s_channel_fmt_t)I2S_CHANNEL_FMT_ONLY_RIGHT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = 0,
        .dma_buf_count = 2,
        .dma_buf_len = 1024,
        .use_apll = true
    };
    i2s_driver_install(I2S_NUM_1, &i2s_config, 0, NULL);
    i2s_pin_config_t pin_config = 
    {
        .bck_io_num = 13,
        .ws_io_num = 14,
        .data_out_num = -1,
        .data_in_num = 35 
    };
    i2s_set_pin(I2S_NUM_1, &pin_config);
    es8218e_start();
}
void microphone_update_t(int loudness)
{
    _loudness = loudness;
}

int microphone_loudness()
{
    return _loudness;
}
static const char *ES_TAG = "ES8218E_DRIVER";

#define ES_ASSERT(a, format, b, ...) \
    if ((a) != 0) { \
        ESP_LOGE(ES_TAG, format, ##__VA_ARGS__); \
        return b;\
    }

void es8218e_read_all()
{
    for(int16_t i = 0; i < 50; i++)
    {
        uint8_t reg;
        i2c_master_read_reg_t(I2C_NUM_1, ES8218E_ADDR, i, &reg);
    }
}

void es8218e_reset(void)
{
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_RESET, 0x3f);
    delay(1);
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_RESET, 0x00);
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_RESET, 0x80);
}

void es8218e_start(void)
{
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_RESET, 0x3f);
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_RESET, 0x00);
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_CLOCK_MANAGER1, 0x10);
    delay(1);
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_CLOCK_MANAGER1, 0x00);
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_CLOCK_MANAGER1, 0x0f);    //slave mode
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_CLOCK_MANAGER2, 0x01);    //1
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_CLOCK_MANAGER3, 0x20);    //4096000/16000/8 = 32
    // mb_esp32_i2c_master_write_reg_t(ES8218E_ADDR, 0x06, 0x00);                      //
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_SERIAL_DATA_PORT, 0x0c);  //16 bit data, i2s format(0x0c）  //left justify 0x0d
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_ADC_CONTROL2, 0x18);      //high pass filter     //0x18 open   0x00 close
                                                //0x18(adc soft ramp and high pass filter) //0x10(adc soft ramp)
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_ADC_CONTROL6, 0xA0);      //ALCLVL=-1.5db
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_SYSTEM_CONTROL6, 0x30);   //POWER-INI time
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_SYSTEM_CONTROL7, 0x20);   //POWER-UP time
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_ADC_CONTROL10, 0x04);     //HPF slow setting coeff defalut value
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_ADC_CONTROL11, 0x04);     //HPF fast setting coeff defalut value
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_ADC_CONTROL1, 0x32);      //LIN2/RIN2, PGA=+18db(0x30)   PGA = 0db(0x20)   //0x20
                                                //低三位，0(0db) 1(3.5db) 2(6db) 3(9db) 4(12db) 5(15db) 6(18db)
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_SYSTEM_CONTROL1, 0x00);   //POWER ON
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_RESET, 0x80);             //IC start

    uint8_t pga_gain = 0xc0 | (uint8_t)((20.5 + 6.5)/1.5);
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_ADC_CONTROL4, pga_gain);  //ALC ON
    // mb_esp32_i2c_master_write_reg_t(ES8218E_ADDR, ES8218E_ADC_CONTROL4, 0x1c);   //ALC OFF
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_ADCVOLUMEL, 0x00);        //0db
}

void es8218e_stop( )
{
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_CLOCK_MANAGER1, 0x80); //enable dac
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_CLOCK_MANAGER1, 0x00); // 0x00 audio on LIN1&RIN1,  0x09 LIN2&RIN2
}

void es8218e_config_fmt(es_i2s_fmt_t fmt)
{
    uint8_t reg = 0;
    i2c_master_read_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_SERIAL_DATA_PORT, &reg);
    reg = reg & 0xfc;
    i2c_master_write_reg_t(I2C_NUM_1, ES8218E_ADDR, ES8218E_SERIAL_DATA_PORT, reg | fmt);
}