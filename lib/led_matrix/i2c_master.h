#ifndef _I2C_MASTER_H_
#define _I2C_MASTER_H_
#ifdef __cplusplus
extern "C" {
#endif
    #define I2C_STATUS_NOT_INIT   (0)
    #define I2C_STATUS_INIT       (1)

    typedef struct
    {
        int i2c_master_port;
        uint8_t i2c_mode; // I2C_MODE_MASTER
        uint8_t sda_io_num ; //  I2C_SDA_IO;
        uint8_t sda_pullup_en; // GPIO_PULLUP_DISABLE;
        uint8_t scl_io_num; // I2C_SCL_IO;
        uint8_t scl_pullup_en; //  GPIO_PULLUP_DISABLE;
        uint8_t slaver_address;

        uint32_t clk_speed; //  I2C_FREQ_HZ;
    }i2c_master_structure_t;

    esp_err_t i2c_master_init_t(const i2c_master_structure_t *i2c_config);
    esp_err_t i2c_master_deinit_t(int32_t port);
    esp_err_t i2c_master_write_reg_t(int32_t port, uint8_t slaver_addr, uint8_t reg, uint8_t data);
    esp_err_t i2c_master_write_datas_t(int32_t port, uint8_t slaver_addr, uint8_t reg_addr, uint8_t *data, uint16_t size);
    esp_err_t i2c_master_read_reg_t(int32_t port, uint8_t slaver_addr, uint8_t reg_addr, uint8_t *data);
    esp_err_t i2c_master_read_datas_t(int32_t port, uint8_t slaver_addr, uint8_t start, uint8_t *buffer, uint16_t size);
    esp_err_t i2c_bus_drive_restore(int scl_io_num, int sda_io_num);
#ifdef __cplusplus
}
#endif
#endif
