#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "driver/gpio.h"
#include "driver/i2c.h"

#include "i2c_master.h"
#include "sled173x_reg.h"
#include "LED_Type3RGBTable.h"
#include "LED_Type4RGBTable.h"

/******************************************************************************
 DEFINE MACROS
 ******************************************************************************/
#define TAG ("sled_1732")

#define I2C_NUM (I2C_NUM_1)
#define SLAVER_ADDRESS (SLED173X_DEFAULT_ADDRESS)
#define LED_MATRIX_SIZE (12)
#define LED_INDEX_MAX (66)
#define SEND_BUFFER_SIZE (256)

/******************************************************************************
 DEFINE TYPES & CONSTANTS
 ******************************************************************************/
typedef struct
{
    uint8_t rgb_led_id;
    uint8_t rgb_component_id[3];

} sled173x_rgb_to_led_id_table_t;

const uint8_t tabLED_Type4Vaf[36] =
    {
        0x55, 0x55, 0x55, // C1-A ~ C1-L
        0x55, 0x55, 0x55, // C2-A ~ C2-L
        0x55, 0x55, 0x55, // C3-A ~ C3-L
        0x55, 0x55, 0x55, // C4-A ~ C4-L
        0x55, 0x55, 0x55, // C5-A ~ C5-L
        0x55, 0x55, 0x55, // C6-A ~ C6-L
        0x55, 0x55, 0x55, // C7-A ~ C7-L
        0x55, 0x55, 0x55, // C8-A ~ C8-L
        0x55, 0x55, 0x55, // C9-A ~ C9-L
        0x55, 0x55, 0x55, // C10-A ~ C10-L
        0x55, 0x55, 0x55, // C11-A ~ C11-L
        0x55, 0x55, 0x55, // C12-A ~ C12-L
};

const sled173x_rgb_to_led_id_table_t sled173x_rgb_to_led_id_table[LED_MATRIX_SIZE] =
    {
        {6, {41, 53, 65}},
        {7, {40, 52, 64}},
        {8, {39, 51, 63}},
        {9, {38, 50, 62}},
        {10, {37, 49, 61}},
        {11, {36, 48, 60}},
        {0, {0, 12, 24}},
        {1, {1, 13, 25}},
        {2, {2, 14, 26}},
        {3, {3, 15, 27}},
        {4, {4, 16, 28}},
        {5, {5, 17, 29}},
};

/******************************************************************************
 DECLARE PRIVATE DATAS
 ******************************************************************************/
uint8_t s_i2c_send_buffer[SEND_BUFFER_SIZE];

/******************************************************************************
 DECLARE PUBLIC FUNCTIONS
 ******************************************************************************/

/******************************************************************************
 DECLARE PRIVATE FUNCTIONS
 ******************************************************************************/
#define led_select_frame1_page i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, CONFIGURE_CMD_PAGE, FRAME1_PAGE);
#define led_select_frame2_page i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, CONFIGURE_CMD_PAGE, FRAME2_PAGE);
#define led_select_function_page i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, CONFIGURE_CMD_PAGE, FUNCTION_PAGE);
#define led_select_detection_page i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, CONFIGURE_CMD_PAGE, DETECTION_PAGE);
#define led_select_ledvaf_page i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, CONFIGURE_CMD_PAGE, LED_VAF_PAGE);

static void LED_Type124ClearFrame1Page(void);

/******************************************************************************
 DEFINE PUBLIC FUNCTIONS
 ******************************************************************************/
/* i2c working only this gpio is high level, never drop it down whne system runing */

esp_err_t sled173x_led_update_all_t(uint8_t *data, uint16_t len)
{
    uint8_t temp_data[LED_INDEX_MAX] = {0x00};
    led_select_frame1_page;
    for (uint16_t i = 0; i < len; i++)
    {
        temp_data[sled173x_rgb_to_led_id_table[(uint8_t)(i / 3)].rgb_component_id[(uint8_t)(i % 3)]] = *(data + i);
    }
    i2c_master_write_datas_t(I2C_NUM, SLAVER_ADDRESS, TYPE4_PWM_FRAME_FIRST_ADDR, temp_data, LED_INDEX_MAX);

    return 0;
}

esp_err_t sled173x_type4_config_t(void)
{
    /* Setting SLED1735 Ram Page to Function Page */
    led_select_function_page;
    /* System must go to SW shutdowm mode when initialization */
    i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, SW_SHUT_DOWN_REG, mskSW_SHUT_DOWN_MODE);
    /* Setting Matrix Type = Type3 */
    i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, PICTURE_DISPLAY_REG, mskMATRIX_TYPE_TYPE4);
    /* Setting Staggered Delay */
    i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, STAGGERED_DELAY_REG, ((mskSTD4 & CONST_STD_GROUP4) | (mskSTD3 & CONST_STD_GROUP3) | (mskSTD2 & CONST_STD_GROUP2) | (mskSTD1 & CONST_STD_GROUP1)));
    /* Enable Slew Rate control */
    i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, SLEW_RATE_CTL_REG, mskSLEW_RATE_CTL_EN);

    //===============================================================
    // VAF Control settings base on the LED type.
    //================================================================
    i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, VAF_CTL_REG, (mskVAF2 | mskVAF1));
    i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, VAF_CTL_REG2, (mskFORCEVAFCTL_ALWAYSON | mskTP4VAF3));
    i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, TYPE4_VAF_REG1, (mskTYPE4_CB7_VAF3 | mskTYPE4_CB6_VAF3 | mskTYPE4_CB5_VAF3 | mskTYPE4_CB4_VAF3));
    i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, TYPE4_VAF_REG2, (mskTYPE4_CC2_VAF3 | mskTYPE4_CC1_VAF3 | mskTYPE4_CB9_VAF3 | mskTYPE4_CB8_VAF3));
    i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, TYPE4_VAF_REG3, (mskTYPE4_CC6_VAF3 | mskTYPE4_CC5_VAF3 | mskTYPE4_CC4_VAF3 | mskTYPE4_CC3_VAF3));
    //================================================================

    // Setting LED driving current = 40mA and Enable current control
    i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, CURRENT_CTL_REG, (mskCURRENT_CTL_EN | CONST_CURRENT_STEP_20mA));

    // Init Frame1Page(Clear all Ram)
    LED_Type124ClearFrame1Page();

    //======================================================//
    // Init Type4 FrameVAFPage : Single R/G/B ,              //
    // Anode RGB or Cathode RGB have different VAF settings  //
    // which can choice by " TYPE4_VAF_OPTION ".             //
    //======================================================//
    led_select_ledvaf_page;
    for (uint16_t i = 0; i < TYPE4_VAF_FRAME_LENGTH; i++)
    {
        s_i2c_send_buffer[i] = tabLED_Type4Vaf[i];
    }
    i2c_master_write_datas_t(I2C_NUM, SLAVER_ADDRESS, TYPE4_VAF_FRAME_FIRST_ADDR, s_i2c_send_buffer, TYPE4_VAF_FRAME_LENGTH);

    // After initialization , system back to SW Normal mode.
    led_select_function_page;
    i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, SW_SHUT_DOWN_REG, mskSW_NORMAL_MODE);

    /********************************************************************************************/
    /* Turn Off all LED Panel */
    /* we use pwm to control the leds */
    led_select_frame1_page;
    for (uint16_t i = 0; i < TYPE4_LED_FRAME_LENGTH; i++)
    {
        s_i2c_send_buffer[i] = TYPE4_LED_FRAME_CLR_DATA;
    }
    i2c_master_write_datas_t(I2C_NUM, SLAVER_ADDRESS, TYPE4_LED_FRAME_FIRST_ADDR, s_i2c_send_buffer, TYPE4_LED_FRAME_LENGTH);
    led_select_frame2_page;
    for (uint16_t i = 0; i < TYPE4_LED_FRAME_LENGTH; i++)
    {
        s_i2c_send_buffer[i] = TYPE4_LED_FRAME_CLR_DATA;
    }
    i2c_master_write_datas_t(I2C_NUM, SLAVER_ADDRESS, TYPE4_LED_FRAME_FIRST_ADDR, s_i2c_send_buffer, TYPE4_LED_FRAME_LENGTH);

    /* SET PWM CTL Registers Value =0x00(Max Value, Frame1Page) */
    led_select_frame1_page;
    for (uint16_t i = 0; i < TYPE4_PWM_FRAME_LENGTH; i++)
    {
        s_i2c_send_buffer[i] = TYPE4_PWM_FRAME_CLR_DATA;
    }
    i2c_master_write_datas_t(I2C_NUM, SLAVER_ADDRESS, TYPE4_PWM_FRAME_FIRST_ADDR, s_i2c_send_buffer, TYPE4_PWM_FRAME_LENGTH);
    led_select_frame2_page;
    for (uint16_t i = 0; i < TYPE4_PWM_FRAME_LENGTH; i++)
    {
        s_i2c_send_buffer[i] = TYPE4_PWM_FRAME_CLR_DATA;
    }
    i2c_master_write_datas_t(I2C_NUM, SLAVER_ADDRESS, TYPE4_PWM_FRAME_FIRST_ADDR, s_i2c_send_buffer, TYPE4_PWM_FRAME_LENGTH);

    /* set default status */
    led_select_frame1_page;
    for (uint16_t i = 0; i < TYPE4_PWM_FRAME_LENGTH; i++)
    {
        s_i2c_send_buffer[i] = TYPE4_PWM_FRAME_CLR_DATA;
    }
    i2c_master_write_datas_t(I2C_NUM, SLAVER_ADDRESS, TYPE4_PWM_FRAME_FIRST_ADDR, s_i2c_send_buffer, TYPE4_PWM_FRAME_LENGTH);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    led_select_frame1_page;
    for (uint16_t i = 0; i < TYPE4_LED_FRAME_LENGTH; i++)
    {
        s_i2c_send_buffer[i] = TYPE4_LED_FRAME_MAX_DATA;
    }
    i2c_master_write_datas_t(I2C_NUM, SLAVER_ADDRESS, TYPE4_LED_FRAME_FIRST_ADDR, s_i2c_send_buffer, TYPE4_LED_FRAME_LENGTH);

    return 0;
}

/******************************************************************************
 DEFINE PRIVATE FUNCTIONS
 ******************************************************************************/
static void LED_Type124ClearFrame1Page(void)
{
    // Setting SLED1735 Ram Page to Frame 1 Page
    led_select_frame1_page;
    // Write Data=0x00 to bI2C_MasTxData[] FIFO to CLR SLED1735 Ram
    for (uint16_t i = 0; i < TYPE1_2_4_FRAME1PAGE_LENGTH; i++)
    {
        s_i2c_send_buffer[i] = TYPE1_LED_FRAME_CLR_DATA;
    }

    // send 0xB3 bytes length Data From address 0x00
    i2c_master_write_datas_t(I2C_NUM, SLAVER_ADDRESS, (mskLED_FRAME_REG_ADDR & 0x00), s_i2c_send_buffer, TYPE1_2_4_FRAME1PAGE_LENGTH);
}
