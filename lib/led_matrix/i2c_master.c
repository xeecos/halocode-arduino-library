#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h> 

#include "esp_log.h"
#include "driver/i2c.h" 
#include "driver/gpio.h"

#include "i2c_master.h"

/******************************************************************************
 DEFINE MACROS
 ******************************************************************************/
#define TAG                        ("i2c_master")

#define I2C_TX_BUF_DISABLE         (0)  /*!< I2C master do not need buffer */
#define I2C_RX_BUF_DISABLE         (0)   /*!< I2C master do not need buffer */

#define WRITE_B                    I2C_MASTER_WRITE /*!< I2C master write */
#define READ_B                     I2C_MASTER_READ /*!< I2C master read */
#define ACK_CHECK_E                (0x1)    /*!< I2C master will check ack from slave*/
#define ACK_CHECK_D                (0x0)    /*!< I2C master will not check ack from slave */
#define ACK_V                      (0x0)    /*!< I2C ack value */
#define NACK_V                     (0x1)    /*!< I2C nack value */

#define SLAVER_ADDRESS_EXAMPLE     (0xff) 
#define I2C_FREQUENCY_EXAMPLE      (400000)

#define RW_WAIT_MAX_TIME_MS        (100)

/******************************************************************************
 DEFINE TYPES & CONSTANTS
 ******************************************************************************/
typedef struct
{
  int i2c_0_status;
  int i2c_1_status;
}i2c_status_t;

/******************************************************************************
 DECLARE PRIVATE DATAS
 ******************************************************************************/
i2c_status_t i2c_status = {.i2c_0_status = I2C_STATUS_NOT_INIT,
                                             .i2c_1_status = I2C_STATUS_NOT_INIT};

/******************************************************************************
 DECLARE PRIVATE FUNCTIONS
 ******************************************************************************/
static esp_err_t i2c_master_config_t(const i2c_master_structure_t *i2c_config);
static esp_err_t i2c_drive_check(uint8_t gpio_num);
static esp_err_t i2c_bus_check(int scl_io_num, int sda_io_num);

/******************************************************************************
 DEFINE PUBLIC FUNCTIONS
 ******************************************************************************/
esp_err_t i2c_master_init_t(const i2c_master_structure_t *i2c_config)
{
  if(i2c_config->i2c_master_port == I2C_NUM_0)
  {
    if(i2c_status.i2c_0_status == I2C_STATUS_INIT)
    {
      return 0;
    }
  }
  else if(i2c_config->i2c_master_port == I2C_NUM_1)
  {
    if(i2c_status.i2c_1_status == I2C_STATUS_INIT)
    {
      return 0;
    }
  }

  if(i2c_master_config_t(i2c_config) != 0)
  {
    return -1;
  }
  else
  {
    if(i2c_config->i2c_master_port == I2C_NUM_0)
    {
      i2c_status.i2c_0_status = I2C_STATUS_INIT;
    }
    else if(i2c_config->i2c_master_port == I2C_NUM_1)
    {
      i2c_status.i2c_1_status = I2C_STATUS_INIT;
    }
  }
  return 0;
}

esp_err_t i2c_master_deinit_t(int32_t port)
{ 
  if(port == I2C_NUM_0)
  {
    if(i2c_status.i2c_0_status == I2C_STATUS_NOT_INIT)
    {
      return 0;
    }
  }
  else if(port == I2C_NUM_1)
  {
    if(i2c_status.i2c_1_status == I2C_STATUS_NOT_INIT)
    {
      return 0;
    }
  }

  esp_err_t res = ESP_OK;
  res = res | i2c_reset_tx_fifo(port);
  res = res | i2c_reset_rx_fifo(port);
  res = res | i2c_driver_delete(port); 

  return res;
}

esp_err_t i2c_bus_drive_restore(int scl_io_num, int sda_io_num)
{
  uint32_t i2c_clk_cnt;
  gpio_config_t io_conf;
 
  io_conf.intr_type = GPIO_PIN_INTR_DISABLE;   
  io_conf.mode = GPIO_MODE_INPUT_OUTPUT_OD;
  io_conf.pin_bit_mask = (1 << scl_io_num);
  io_conf.pull_down_en = 0;
  io_conf.pull_up_en = 0;
  gpio_config(&io_conf);

  i2c_clk_cnt = 0;  
  while(ESP_OK != i2c_bus_check(scl_io_num, sda_io_num) && i2c_clk_cnt++ < 60)
  {
    gpio_set_level(scl_io_num, 0);
    vTaskDelay(2 / portTICK_PERIOD_MS);
    gpio_set_level(scl_io_num, 1);
    vTaskDelay(2 / portTICK_PERIOD_MS);
  }

  if(i2c_clk_cnt < 60)
  {
    return 0;
  }
  else
  {
    return -1;
  }
}
 
esp_err_t i2c_master_write_reg_t(int32_t port, uint8_t slaver_addr, uint8_t reg, uint8_t data)
{
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();  // create a command link,command data will be added to this link and then sent at once
  i2c_master_start(cmd);                         // I2C logic has been packaged in these functions
  i2c_master_write_byte(cmd, (slaver_addr << 1) | WRITE_B, ACK_CHECK_E);
  i2c_master_write(cmd, &reg, 1, ACK_CHECK_E);
  i2c_master_write(cmd, &data, 1, ACK_CHECK_E);
  i2c_master_stop(cmd);
  esp_err_t res = i2c_master_cmd_begin(port, cmd, RW_WAIT_MAX_TIME_MS / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);
  return res;
}

esp_err_t i2c_master_write_datas_t(int32_t port, uint8_t slaver_addr, uint8_t reg_addr, uint8_t *data, uint16_t size)
{
  if(size == 0)
  {
    return -1;
  }
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();  // create a command link,command data will be added to this link and then sent at once
  i2c_master_start(cmd);                         // I2C logic has been packaged in these functions
  i2c_master_write_byte(cmd, (slaver_addr << 1) | WRITE_B, ACK_CHECK_E);
  i2c_master_write(cmd, &reg_addr, 1, ACK_CHECK_E);
  for(uint16_t i = 0; i < size; i++)
  {
    i2c_master_write(cmd, (data + i), 1, ACK_CHECK_E);
  }
  
  i2c_master_stop(cmd);
  esp_err_t res = i2c_master_cmd_begin(port, cmd, RW_WAIT_MAX_TIME_MS / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);
  return res;
}

esp_err_t i2c_master_read_reg_t(int32_t port, uint8_t slaver_addr, uint8_t reg_addr, uint8_t *data)
{
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, (slaver_addr << 1) | WRITE_B, ACK_CHECK_E);
  i2c_master_write(cmd, &reg_addr, 1, ACK_CHECK_E);

  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, (slaver_addr << 1) | READ_B, ACK_CHECK_E);
  i2c_master_read_byte(cmd, data, NACK_V);
  i2c_master_stop(cmd);
  esp_err_t res = i2c_master_cmd_begin(port, cmd, RW_WAIT_MAX_TIME_MS / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);
  return res;
}

esp_err_t i2c_master_read_datas_t(int32_t port, uint8_t slaver_addr, uint8_t start, uint8_t *buffer, uint16_t size)
{
  if(size == 0)
  {
    return -1;
  }
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, (slaver_addr << 1) | WRITE_B, ACK_CHECK_E);
  i2c_master_write(cmd, &start, 1, ACK_CHECK_E);

  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, (slaver_addr << 1) | READ_B, ACK_CHECK_E);
  if(size > 1) 
  {
    i2c_master_read(cmd, buffer, size - 1, ACK_V);
  }
  i2c_master_read_byte(cmd, buffer + size - 1, NACK_V); //the lastest byte will not give a ASK
  i2c_master_stop(cmd);
  esp_err_t res = i2c_master_cmd_begin(port, cmd, RW_WAIT_MAX_TIME_MS / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);
  return res;
}

/******************************************************************************
 DEFINE PRIVATE FUNCTIONS
 ******************************************************************************/
static esp_err_t i2c_master_config_t(const i2c_master_structure_t *i2c_config)
{
  if(0 != i2c_bus_drive_restore(i2c_config->scl_io_num, i2c_config->sda_io_num))
  {
    return -1;
  }
  
  /* Note: before configing i2c, set the gpio to default status,
   * or, the i2c may not work
   */
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_PIN_INTR_DISABLE;   
  io_conf.mode = GPIO_MODE_DISABLE;
  io_conf.pin_bit_mask = (1 << i2c_config->scl_io_num);
  io_conf.pull_down_en = 0;
  io_conf.pull_up_en = 0;
  gpio_config(&io_conf);
  io_conf.pin_bit_mask = (1 << i2c_config->sda_io_num);
  gpio_config(&io_conf);

  i2c_config_t conf; 
  conf.mode = i2c_config->i2c_mode;
  conf.sda_io_num = i2c_config->sda_io_num;
  conf.sda_pullup_en = i2c_config->sda_pullup_en;
  conf.scl_io_num = i2c_config->scl_io_num ;
  conf.scl_pullup_en = i2c_config->scl_pullup_en;
  conf.master.clk_speed = i2c_config->clk_speed; 
  esp_err_t res = ESP_OK;
  res = res | i2c_param_config(i2c_config->i2c_master_port, &conf);
  res = res | i2c_driver_install(i2c_config->i2c_master_port, conf.mode, I2C_RX_BUF_DISABLE, I2C_TX_BUF_DISABLE, 0);

  if(res == ESP_OK)
  {
    return 0;
  }
  else
  {
    return -1;
  }
}

static esp_err_t i2c_drive_check(uint8_t gpio_num)
{
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_PIN_INTR_DISABLE;   
  io_conf.mode = GPIO_MODE_INPUT_OUTPUT_OD;
  io_conf.pin_bit_mask = ((uint64_t)1 << gpio_num);
  io_conf.pull_down_en = 0;
  io_conf.pull_up_en = 0;
  gpio_config(&io_conf);

  // output high and read must be high
  gpio_set_level(gpio_num, 1);
  if(1 != gpio_get_level(gpio_num))
  {
    return ESP_FAIL;
  }

  // output low and read must be low
  gpio_set_level(gpio_num, 0);
  if(0 != gpio_get_level(gpio_num))
  {
    return ESP_FAIL;
  }

  return ESP_OK;
}
 
static esp_err_t i2c_bus_check(int scl_io_num, int sda_io_num)
{
  esp_err_t ret;
 
  ret = i2c_drive_check(scl_io_num);
  if(ESP_OK != ret)
  {
    return ret;
  }

  ret = i2c_drive_check(sda_io_num);
  if(ESP_OK != ret)
  {
    return ret;
  }
  return ret;
}
 