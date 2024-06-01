#include <stdint.h>
#include <string.h>
#include <stdio.h>


#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

#include "sled173x_driver.h"
#include "led_matrix.h"

/******************************************************************************
 DEFINE MACROS
 ******************************************************************************/

#define LED_MATRIX_SIZE (12)
#define RGB_VALUE_MAX (0xff)

#define MODULE_LEDMATRIX_STATUS_CHECK(a, str, ret_val)        \
    if ((a) != led_matrix_structure.module_led_matrix_status) \
    {                                                         \
        return (ret_val);                                     \
    }

#define LED_ID_CHECK(a, str, ret_val)      \
    if ((a) >= LED_MATRIX_SIZE || (a) < 0) \
    {                                      \
        return (ret_val);                  \
    }

#define LED_RGB_VALUE_LIMIT(a) \
    ((a) > RGB_VALUE_MAX ? RGB_VALUE_MAX : (a));

/******************************************************************************
 DEFINE TYPES & CONSTANTS
 ******************************************************************************/
typedef struct
{
    int module_led_matrix_status;
    uint8_t led_matrix_rgb_compoment[LED_MATRIX_SIZE][3];
    uint8_t led_matrix_rgb_compoment_last[LED_MATRIX_SIZE][3];
    SemaphoreHandle_t update_mutex;
    int driver_id;
} led_matrix_structure_t;

/******************************************************************************
 DECLARE PRIVATE DATAS
 ******************************************************************************/
led_matrix_structure_t led_matrix_structure;

#define MODULE_LED_MATRIX_STATUS_CHECK(a, str, ret_val)       \
    if ((a) != led_matrix_structure.module_led_matrix_status) \
    {                                                         \
        return (ret_val);                                     \
    }

#define LED_UPDATE_ENTER xSemaphoreTake(led_matrix_structure.update_mutex, portMAX_DELAY);
#define LED_UPDATE_EXIT xSemaphoreGive(led_matrix_structure.update_mutex);

/******************************************************************************
 DECLARE PUBLIC FUNCTIONS
 ******************************************************************************/

/******************************************************************************
 DECLARE PRIVATE FUNCTIONS
 ******************************************************************************/
static esp_err_t led_matrix_config_t(void);
static bool is_led_rgb_components_update_t(void);
static void led_rgb_components_sync_t(void);
static esp_err_t led_matrix_set_single_led_buffer_t(uint8_t led_id, uint8_t red, uint8_t green, uint8_t blue);

/******************************************************************************
 DEFINE PUBLIC FUNCTIONS
 ******************************************************************************/
/* this function must be called before led_matrix_init_t,
 * the default value is USE_DRIVER_SLED173x
 */
void led_matrix_set_driver_t(int driver_id)
{
    /* choose the driver of leds */
    led_matrix_structure.driver_id = USE_DRIVER_SLED173x;
}

void led_matrix_init_t(void)
{

    led_matrix_structure.update_mutex = xSemaphoreCreateMutex();
    xSemaphoreGive(led_matrix_structure.update_mutex);
    if (led_matrix_structure.update_mutex == NULL)
    {
        return;
    }

    if (0 != led_matrix_config_t())
    {
        return;
    }
    led_matrix_clear();
    led_matrix_structure.module_led_matrix_status = 0;
}

void led_matrix_clear(void)
{
    LED_UPDATE_ENTER
    for (uint8_t i = 0; i < LED_MATRIX_SIZE; i++)
    {
        led_matrix_set_single_led_buffer_t(i, 0, 0, 0);
    }
    LED_UPDATE_EXIT
}

void led_matrix_set_all_led(uint8_t red, uint8_t green, uint8_t blue)
{
    LED_UPDATE_ENTER
    for (uint8_t i = 0; i < LED_MATRIX_SIZE; i++)
    {
        led_matrix_set_single_led_buffer_t(i, red, green, blue);
    }
    LED_UPDATE_EXIT
}

void led_matrix_set_single_led(uint8_t led_id, uint8_t red, uint8_t green, uint8_t blue)
{
    LED_UPDATE_ENTER
    led_matrix_set_single_led_buffer_t(led_id, red, green, blue);
    LED_UPDATE_EXIT
}

void led_matrix_get_all_led_info_t(uint8_t *data, int len)
{
    LED_UPDATE_ENTER
    if (len > LED_MATRIX_SIZE * 3)
    {
        len = LED_MATRIX_SIZE * 3;
    }

    memcpy(data, led_matrix_structure.led_matrix_rgb_compoment_last, len);
    LED_UPDATE_EXIT
}

void led_matrix_is_updated_t(bool *sta)
{
    if (memcpy(led_matrix_structure.led_matrix_rgb_compoment, led_matrix_structure.led_matrix_rgb_compoment_last, LED_MATRIX_SIZE * 3) == 0)
    {
        (*sta) = true;
    }
    else
    {
        (*sta) = false;
    }
}

void led_matrix_set_all_led_info_t(uint8_t *data, int len)
{
    LED_UPDATE_ENTER
    if (len > LED_MATRIX_SIZE * 3)
    {
        len = LED_MATRIX_SIZE * 3;
    }
    memcpy(led_matrix_structure.led_matrix_rgb_compoment, data, len);
    LED_UPDATE_EXIT
}

void led_matrix_set_colorful_led(uint8_t *data, int len, int offset)
{
    LED_UPDATE_ENTER
    len = (len > LED_MATRIX_SIZE * 3) ? LED_MATRIX_SIZE * 3 : len;
    uint8_t led_num = (uint8_t)(len / 3);
    while (offset < 0)
    {
        offset += LED_MATRIX_SIZE;
    }
    uint8_t index = offset;

    for (int i = 0; i < led_num; i++)
    {
        index = offset % LED_MATRIX_SIZE;
        led_matrix_set_single_led_buffer_t(index, data[3 * i], data[3 * i + 1], data[3 * i + 2]);
        offset++;
    }

    LED_UPDATE_EXIT
}

void led_matrix_update(void)
{
    if (is_led_rgb_components_update_t())
    {
        LED_UPDATE_ENTER
        sled173x_led_update_all_t((uint8_t *)led_matrix_structure.led_matrix_rgb_compoment, LED_MATRIX_SIZE * 3);
        led_rgb_components_sync_t();
    }
    LED_UPDATE_EXIT
}

/******************************************************************************
 DEFINE PRIVATE FUNCTIONS
 ******************************************************************************/
static esp_err_t led_matrix_config_t(void)
{
    if (led_matrix_structure.module_led_matrix_status != 1)
    {

        sled173x_type4_config_t();
        memset(led_matrix_structure.led_matrix_rgb_compoment, 0x00, LED_MATRIX_SIZE * 3);
        memset(led_matrix_structure.led_matrix_rgb_compoment_last, 0x00, LED_MATRIX_SIZE * 3);

        led_matrix_structure.module_led_matrix_status = 1;

        return 0;
    }
    return 0;
}

static esp_err_t led_matrix_set_single_led_buffer_t(uint8_t led_id, uint8_t red, uint8_t green, uint8_t blue)
{
    red = LED_RGB_VALUE_LIMIT(red);
    green = LED_RGB_VALUE_LIMIT(green);
    blue = LED_RGB_VALUE_LIMIT(blue);
    led_matrix_structure.led_matrix_rgb_compoment[led_id][0] = red;
    led_matrix_structure.led_matrix_rgb_compoment[led_id][1] = green;
    led_matrix_structure.led_matrix_rgb_compoment[led_id][2] = blue;

    return 0;
}

static bool is_led_rgb_components_update_t(void)
{
    if (memcmp(led_matrix_structure.led_matrix_rgb_compoment,
               led_matrix_structure.led_matrix_rgb_compoment_last, LED_MATRIX_SIZE * 3))
    {
        return true;
    }
    else
    {
        return false;
    }
}

static void led_rgb_components_sync_t(void)
{
    memcpy(led_matrix_structure.led_matrix_rgb_compoment_last,
           led_matrix_structure.led_matrix_rgb_compoment, LED_MATRIX_SIZE * 3);
}
