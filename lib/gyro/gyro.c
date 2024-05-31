#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "driver/i2c.h"
#include "driver/gpio.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "i2c_master.h"

#include "gyro.h"

#define ACCELEROMETER_QMA6981 (0)
#define GYRO_MPU6887 (1)

#if ACCELEROMETER_QMA6981
#include "qma6981_reg.h"
#endif /* ACCELEROMETER_QMA6981 */

#if GYRO_MPU6887
#include "mpu6887_reg.h"
#endif /* GYRO_MPU6887 */

/******************************************************************************
 DEFINE MACROS
 ******************************************************************************/
#ifndef PRODUCT_I2C_SDA_IO
#define I2C_SDA_IO (19)
#else
#define I2C_SDA_IO PRODUCT_I2C_SDA_IO
#endif

#ifndef PRODUCT_I2C_SCL_IO
#define I2C_SCL_IO (18)
#else
#define I2C_SCL_IO PRODUCT_I2C_SCL_IO
#endif

#if ACCELEROMETER_QMA6981
#define SLAVER_ADDRESS (QMA6981_DEFAULT_ADDRESS)
#endif

#if GYRO_MPU6887
#define SLAVER_ADDRESS (MPU6887_DEFAULT_ADDRESS)
#endif

#define MAX_I2C_RESTORE_SCL_CNT (8 * 32)
#define PI (3.1415926)
#define ACC_FILTER (0.8)
#define TILT_ANGLE_FILTER (0.9)
#define TILT_RANGE_GAIN (0.2588)              // cos(75)
#define ARROW_ORIENTATION_RANGE_GAIN (0.2588) // cos(75)
#define SCREEN_STATUS_RANGE_GAIN (0.906)      //  cos(25)
#define SHAKE_CHECK_DATA_BUFFER_SIZE (60)
#define GRAVITY_DEFAULT_VALUE (17000)
#define I2C_NUM (I2C_NUM_1)
#define I2C_FREQUENCY (100000)

#define SHAKE_STRENGTH_FREQUENCY_GAIN (4)                           // this is a empirical value (0 - 20)
#define SHAKE_STRENGTH_ACC_VALUE_GAIN (5.0 / GRAVITY_DEFAULT_VALUE) // this is a empirical value
#define SHAKE_STRENGTH_START_CHECK_GAIN (0.05)

#define SHAKED_THRESHOLD_DEFAULT (20)
#define SHAKED_THRESHOLD_MAX (80)
#define SHAKED_THRESHOLD_MIN (10)

#define GTRO_SENSITIVITY_DEFAULT (65.5) // for 500 deg/s, check data sheet
#define GYRO_UPDATE_THRESHOLD_ACC (100) // acc
#define GYRO_UPDATE_THRESHOLD_GYRO (10) // gyro

/******************************************************************************
 DEFINE TYPES & CONSTANTS
 ******************************************************************************/
typedef struct
{
    int module_gyro_status;
    bool gyro_ope_i2c_flag;
} gyro_operation_manager_t;

typedef struct
{
    float gyro_sensitivity;
    float gyro_x_offs;
    float gyro_y_offs;
    float gyro_z_offs;
} gyro_calibration_t;

typedef struct
{
    float acc_x;
    float acc_y;
    float acc_z;

    float gyro_x;
    float gyro_y;
    float gyro_z;

    float acc_earth;

    bool is_shaked;
    float shaked_threshold;
    float shaked_strength;

    float angle_pitch;
    float angle_yaw;
    float angle_roll;

    float angle_rotate_x;
    float angle_rotate_y;
    float angle_rotate_z;

    uint16_t tilt_status;
    float acc_filter;
} gyro_data_structure_t;

typedef struct
{
    int16_t threshold_value_high;
    int16_t threshold_value_low;
    uint8_t event_occured_flag;
} gyro_event_manager_t;

/******************************************************************************
 DEFINE PRIVATE DATA
 ******************************************************************************/
gyro_operation_manager_t gyro_operation_manager;
gyro_data_structure_t gyro_data_structure;
gyro_calibration_t gyro_calibration;
gyro_event_manager_t gyro_event_info[EVENT_MAX];

static uint32_t shake_detect_zero_pass_flags[4] = {0, 0, 0, 0};

#define TILT_ID_CHECK(a, ret_val)                                                \
    if (!((a >= 0) && (a < EVENT_MAX)))                                          \
    {                                                                            \
        return (ret_val);                                                        \
    }

/******************************************************************************
 DECLARE PRIVATE FUNCTIONS
 ******************************************************************************/
static esp_err_t gyro_config_t(void);
static float gyro_pitch_angle_range_t(float angle);
static float gyro_roll_angle_range_t(float angle);
static void shake_detect_set_zero_pass_flag_t(uint16_t index, bool sta);
static bool shake_detect_get_zero_pass_flag_t(uint16_t index);
static esp_err_t gyro_event_listening_t(float ax, float ay, float az);

/******************************************************************************
 DEFINE PUBLIC FUNCTIONS
 ******************************************************************************/

/******************************************************************************
 DEFINE PUBLIC FUNCTIONS
 ******************************************************************************/
esp_err_t gyro_get_acc_x_t(float *out_val)
{
    (*out_val) = gyro_data_structure.acc_x;
    return 0;
}

esp_err_t gyro_get_acc_y_t(float *out_val)
{
    (*out_val) = gyro_data_structure.acc_y;
    return 0;
}

esp_err_t gyro_get_acc_z_t(float *out_val)
{
    (*out_val) = gyro_data_structure.acc_z;
    return 0;
}

esp_err_t gyro_get_gyro_x_t(float *out_val)
{
    (*out_val) = gyro_data_structure.gyro_x;
    return 0;
}

esp_err_t gyro_get_gyro_y_t(float *out_val)
{
    (*out_val) = gyro_data_structure.gyro_y;
    return 0;
}

esp_err_t gyro_get_gyro_z_t(float *out_val)
{
    (*out_val) = gyro_data_structure.gyro_z;
    return 0;
}

esp_err_t gyro_get_rotate_angle_x_t(float *out_val)
{
    (*out_val) = gyro_data_structure.angle_rotate_x;
    return 0;
}

esp_err_t gyro_get_rotate_angle_y_t(float *out_val)
{
    (*out_val) = gyro_data_structure.angle_rotate_y;
    return 0;
}

esp_err_t gyro_get_rotate_angle_z_t(float *out_val)
{
    (*out_val) = gyro_data_structure.angle_rotate_z;
    return 0;
}

esp_err_t gyro_get_acc_t(float *out_val, uint8_t axis)
{
    if (axis == AXIS_ID_X)
    {
        (*out_val) = gyro_data_structure.acc_x;
    }
    else if (axis == AXIS_ID_Y)
    {
        (*out_val) = gyro_data_structure.acc_y;
    }
    else if (axis == AXIS_ID_Z)
    {
        (*out_val) = gyro_data_structure.acc_z;
    }
    else
    {
        (*out_val) = 0;
        return 0x102;
    }
    return 0;
}

esp_err_t gyro_get_gyro_t(float *out_val, uint8_t axis)
{
    if (axis == AXIS_ID_X)
    {
        (*out_val) = gyro_data_structure.gyro_x;
    }
    else if (axis == AXIS_ID_Y)
    {
        (*out_val) = gyro_data_structure.gyro_y;
    }
    else if (axis == AXIS_ID_Z)
    {
        (*out_val) = gyro_data_structure.gyro_z;
    }
    else
    {
        (*out_val) = 0;
        return 0x102;
    }
    return 0;
}

esp_err_t gyro_get_rotate_angle_t(float *out_val, uint8_t axis)
{
    if (axis == AXIS_ID_X)
    {
        (*out_val) = gyro_data_structure.angle_rotate_x;
    }
    else if (axis == AXIS_ID_Y)
    {
        (*out_val) = gyro_data_structure.angle_rotate_y;
    }
    else if (axis == AXIS_ID_Z)
    {
        (*out_val) = gyro_data_structure.angle_rotate_z;
    }
    else
    {
        (*out_val) = 0;
        return 0x102;
    }
    return 0;
}

esp_err_t gyro_reset_rotate_angle_t(uint8_t axis)
{
    if (axis == AXIS_ID_X)
    {
        gyro_data_structure.angle_rotate_x = 0.0;
    }
    else if (axis == AXIS_ID_Y)
    {
        gyro_data_structure.angle_rotate_y = 0.0;
    }
    else if (axis == AXIS_ID_Z)
    {
        gyro_data_structure.angle_rotate_z = 0.0;
    }
    else
    {
    }
    return 0;
}

esp_err_t gyro_set_shaked_threshold_t(float value)
{
    value = value > SHAKED_THRESHOLD_MAX ? SHAKED_THRESHOLD_MAX : value;
    value = value < SHAKED_THRESHOLD_MIN ? SHAKED_THRESHOLD_MIN : value;

    gyro_data_structure.shaked_threshold = value;
    return 0;
}

esp_err_t gyro_get_shaked_strength_t(float *out_val)
{
    (*out_val) = gyro_data_structure.shaked_strength;
    return 0;
}

esp_err_t gyro_is_shaked_t(bool *out_sta)
{
    (*out_sta) = gyro_data_structure.is_shaked;
    return 0;
}

esp_err_t gyro_get_pitch_angle_t(float *out_val)
{
    (*out_val) = gyro_data_structure.angle_pitch;
    return 0;
}

esp_err_t gyro_get_roll_angle_t(float *out_val)
{
    (*out_val) = gyro_data_structure.angle_roll;
    return 0;
}

esp_err_t gyro_get_yaw_angle_t(float *out_val)
{
    (*out_val) = gyro_data_structure.angle_yaw;
    return 0;
}

esp_err_t gyro_get_tilt_status_t(uint16_t tilt_id, uint16_t *out_sta)
{
    TILT_ID_CHECK(tilt_id, 0x102);

    if (gyro_event_info[tilt_id].event_occured_flag == true)
    {
        (*out_sta) = 1;
    }
    else
    {
        (*out_sta) = 0;
    }
    return 0;
}

esp_err_t gyro_get_all_tilt_status_t(uint16_t *out_sta)
{
    uint16_t ret_status = 0;
    for (uint8_t i = 0; i < EVENT_MAX; i++)
    {
        if (gyro_event_info[i].event_occured_flag == true)
        {
            ret_status |= (1 << i);
        }
        else
        {
            ret_status &= (~(1 << i));
        }
    }
    (*out_sta) = ret_status;
    return 0;
}

/* operation function */
esp_err_t gyro_init_t(void)
{
    i2c_master_structure_t i2c_config;
    i2c_config.i2c_master_port = I2C_NUM;
    i2c_config.i2c_mode = I2C_MODE_MASTER;
    i2c_config.sda_io_num = 19;
    i2c_config.sda_pullup_en = GPIO_PULLUP_DISABLE;
    i2c_config.scl_io_num = 18;
    i2c_config.scl_pullup_en = GPIO_PULLUP_DISABLE;
    i2c_config.clk_speed = I2C_FREQUENCY;

    if (i2c_master_init_t(&i2c_config) == -1)
    {
        gyro_operation_manager.module_gyro_status = 0;
        return -1;
    }

    if (gyro_config_t() != 0)
    {
        return -1;
    }

    gyro_calibration.gyro_sensitivity = GTRO_SENSITIVITY_DEFAULT;
    gyro_calibration.gyro_x_offs = 0;
    gyro_calibration.gyro_y_offs = 0;
    gyro_calibration.gyro_z_offs = 0;

    gyro_data_structure.shaked_threshold = SHAKED_THRESHOLD_DEFAULT;
    gyro_operation_manager.module_gyro_status = 1;
    return 0;
}

esp_err_t gyro_deinit_t(void)
{
    gyro_data_structure.acc_x = 0;
    gyro_data_structure.acc_y = 0;
    gyro_data_structure.acc_z = 0;
    gyro_data_structure.acc_earth = GRAVITY_DEFAULT_VALUE;
    gyro_data_structure.angle_pitch = 0;
    gyro_data_structure.angle_roll = 0;
    gyro_data_structure.is_shaked = false;
    gyro_data_structure.shaked_strength = 0;
    gyro_operation_manager.module_gyro_status = 2;
    return 0;
}

esp_err_t gyro_acc_update_t(void)
{
    static bool first_update = true;
    static float acc_x_static = 0.0;
    static float acc_y_static = 0.0;
    static float acc_z_static = 0.0;

#if ACCELEROMETER_QMA6981
    uint8_t data_buf[6] = {0, 0, 0, 0, 0, 0};
    int16_t acc_value[3] = {0, 0, 0};
    i2c_master_read_datas_t(I2C_NUM, SLAVER_ADDRESS, QMA6981_XOUTL, data_buf, 6);

    acc_value[0] = ((int16_t)data_buf[1] << 2) | ((int16_t)data_buf[0] >> 6);
    acc_value[1] = ((int16_t)data_buf[3] << 2) | ((int16_t)data_buf[2] >> 6);
    acc_value[2] = ((int16_t)data_buf[5] << 2) | ((int16_t)data_buf[4] >> 6);

    for (uint8_t i = 0; i < 3; i++)
    {
        if (acc_value[i] == 0x0200)
        {
            acc_value[i] = -512;
        }
        else if (acc_value[i] & 0x0200)
        {
            acc_value[i] -= 0x1;
            acc_value[i] = ~acc_value[i];
            acc_value[i] &= 0x01ff;
            acc_value[i] = -acc_value[i];
        }
    }
#endif

#if GYRO_MPU6887
    /* 14 = 2 * 3(acc) + 2(tem) + 2 * 3(gyro) */
    uint8_t data_buf[14] = {0};
    int16_t acc_value[3] = {0, 0, 0};
    int16_t gyro_value[3] = {0, 0, 0};
    i2c_master_read_datas_t(I2C_NUM, SLAVER_ADDRESS, ACCEL_XOUT_H, data_buf, 14);

    acc_value[0] = (int16_t)((data_buf[0] << 8) | data_buf[1]);
    acc_value[1] = (int16_t)((data_buf[2] << 8) | data_buf[3]);
    acc_value[2] = (int16_t)((data_buf[4] << 8) | data_buf[5]);

    gyro_value[0] = (int16_t)((data_buf[8] << 8) | data_buf[9]);
    gyro_value[1] = (int16_t)((data_buf[10] << 8) | data_buf[11]);
    gyro_value[2] = (int16_t)((data_buf[12] << 8) | data_buf[13]);

    /* add codes to process gyro data here */
#endif

    /* calculate other value by acc */
    if (first_update)
    {
        acc_x_static = acc_value[0];
        acc_y_static = acc_value[1];
        acc_z_static = acc_value[2];
        first_update = false;
    }
    else
    {
        acc_x_static = acc_x_static * gyro_data_structure.acc_filter + acc_value[0] * (1 - gyro_data_structure.acc_filter);
        acc_y_static = acc_y_static * gyro_data_structure.acc_filter + acc_value[1] * (1 - gyro_data_structure.acc_filter);
        acc_z_static = acc_z_static * gyro_data_structure.acc_filter + acc_value[2] * (1 - gyro_data_structure.acc_filter);
    }
    gyro_data_structure.acc_x = acc_x_static;
    gyro_data_structure.acc_y = acc_y_static;
    gyro_data_structure.acc_z = acc_z_static;

    gyro_data_structure.gyro_x = (gyro_value[0] - gyro_calibration.gyro_x_offs) / gyro_calibration.gyro_sensitivity;
    gyro_data_structure.gyro_y = (gyro_value[1] - gyro_calibration.gyro_y_offs) / gyro_calibration.gyro_sensitivity;
    gyro_data_structure.gyro_z = (gyro_value[2] - gyro_calibration.gyro_z_offs) / gyro_calibration.gyro_sensitivity;

    return 0;
}

/* this function will update the button_structure once */
esp_err_t gyro_update_t(void)
{
    static int32_t update_time_ms = 0;
    static bool first_update_flag = true;
    static float pitch_static = 0.0;
    static float roll_static = 0.0;

    static float s_gx = 0.0;
    static float s_gy = 0.0;
    static float s_gz = 0.0;

    static float acc_x_last = 0.0;
    static float acc_y_last = 0.0;
    static float acc_z_last = 0.0;

    gyro_acc_update_t();
    /* calculate the interval of twice updating */
    float delta_t = 0.0;
    if (first_update_flag)
    {
        update_time_ms = millis();
        delta_t = 0;
    }
    else
    {
        delta_t = (millis() - update_time_ms) / 1000.0;
        update_time_ms = millis();
    }

    /* calculate posture with acc only */
    if (gyro_data_structure.acc_z >= 0)
    {
        roll_static = atan2(gyro_data_structure.acc_x, sqrt(pow(gyro_data_structure.acc_y, 2) + pow(gyro_data_structure.acc_z, 2))) * 180 / PI;
        pitch_static = atan2(gyro_data_structure.acc_y, sqrt(pow(gyro_data_structure.acc_x, 2) + pow(gyro_data_structure.acc_z, 2))) * 180 / PI;
    }
    else
    {
        roll_static = atan2(gyro_data_structure.acc_x, -sqrt(pow(gyro_data_structure.acc_y, 2) + pow(gyro_data_structure.acc_z, 2))) * 180 / PI;
        pitch_static = atan2(gyro_data_structure.acc_y, -sqrt(pow(gyro_data_structure.acc_x, 2) + pow(gyro_data_structure.acc_z, 2))) * 180 / PI;
    }

    /* change the value to 0 - 360 degree */
    if (pitch_static < 0)
    {
        pitch_static = 360 + pitch_static;
    }
    if (roll_static < 0)
    {
        roll_static = 360 + roll_static;
    }

    /* use gyro to calibrate posture */
    if (first_update_flag)
    {
        s_gx = pitch_static;
        s_gy = roll_static;
        s_gz = 0;
        first_update_flag = false;
    }
    else
    {
        s_gx = s_gx + gyro_data_structure.gyro_x * delta_t;
        s_gy = s_gy - gyro_data_structure.gyro_y * delta_t;
        if ((fabs(gyro_data_structure.acc_x - acc_x_last) > GYRO_UPDATE_THRESHOLD_ACC) || (fabs(gyro_data_structure.acc_y - acc_y_last) > GYRO_UPDATE_THRESHOLD_ACC) || (fabs(gyro_data_structure.acc_z - acc_z_last) > GYRO_UPDATE_THRESHOLD_ACC) || (fabs(gyro_data_structure.gyro_z) > GYRO_UPDATE_THRESHOLD_GYRO))
        {
            s_gz = s_gz + gyro_data_structure.gyro_z * delta_t;
            gyro_data_structure.angle_rotate_x += gyro_data_structure.gyro_x * delta_t;
            gyro_data_structure.angle_rotate_y += gyro_data_structure.gyro_y * delta_t;
            gyro_data_structure.angle_rotate_z += gyro_data_structure.gyro_z * delta_t;
        }
        /* limit s_gx and s_gy to -180 ~ 180 */
        if (s_gx < -180)
        {
            s_gx = s_gx + 360;
        }
        if (s_gy < -180)
        {
            s_gy = s_gy + 360;
        }
        /*
        if(s_gz < 0)
        {
          s_gz = s_gz + 360;
        }
        */
        if (s_gx >= 180)
        {
            s_gx = s_gx - 360;
        }
        if (s_gy >= 180)
        {
            s_gy = s_gy - 360;
        }
        /*
        if(s_gz > 360)
        {
          s_gz = s_gz - 360;
        }
        */
    }

    /* if we need to guarantee the accuracy of dynamic process,
     * the filter parameter should be larger */
    /*  TILT_ANGLE_FILTER; --- 0.5 / (0.5 + delta_t) */
    if ((s_gx * pitch_static) < 0 && (fabs(s_gx) > 175 || fabs(pitch_static) > 175))
    {
        s_gx = pitch_static;
    }
    else
    {
        s_gx = s_gx * TILT_ANGLE_FILTER + pitch_static * (1 - TILT_ANGLE_FILTER);
    }
    if ((s_gy * roll_static) < 0 && (fabs(s_gy) > 175 || fabs(roll_static) > 175))
    {
        s_gy = roll_static;
    }
    else
    {
        s_gy = s_gy * TILT_ANGLE_FILTER + roll_static * (1 - TILT_ANGLE_FILTER);
    }

    acc_x_last = gyro_data_structure.acc_x;
    acc_y_last = gyro_data_structure.acc_y;
    acc_z_last = gyro_data_structure.acc_z;

    gyro_data_structure.angle_pitch = gyro_pitch_angle_range_t(pitch_static);
    gyro_data_structure.angle_roll = gyro_roll_angle_range_t(roll_static);
    /* no limitation for yaw  */
    gyro_data_structure.angle_yaw = s_gz;

    /* detect acc event */
    gyro_shake_detect_t();
    gyro_event_listening_t(gyro_data_structure.acc_x, gyro_data_structure.acc_y,
                           gyro_data_structure.acc_z);

    return 0;
}

esp_err_t gyro_test_t(void)
{
    gyro_init_t();
    gyro_event_init_t();
    while (1)
    {
        gyro_update_t();
        gyro_shake_detect_t();
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
    return 0;
}

esp_err_t gyro_calibrate_t(void)
{
    if (1 != gyro_operation_manager.module_gyro_status)
    {
        gyro_data_structure.acc_earth = GRAVITY_DEFAULT_VALUE;
        return -1;
    }

    uint16_t num = 100;
    float acc_static_sum = 0;
    gyro_data_structure.acc_filter = 0.0;
    for (uint16_t i = 0; i < num; i++)
    {
        gyro_acc_update_t();
        acc_static_sum += sqrt(pow(gyro_data_structure.acc_x, 2) + pow(gyro_data_structure.acc_y, 2) + pow(gyro_data_structure.acc_z, 2));
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    gyro_data_structure.acc_filter = ACC_FILTER;

    gyro_data_structure.acc_earth = acc_static_sum / num;

    return 0;
}

esp_err_t gyro_shake_detect_t(void)
{
    static uint16_t acc_filter = 0;
    static bool first_flag = true;
    static uint16_t acc_buffer[SHAKE_CHECK_DATA_BUFFER_SIZE];
    static uint16_t data_in_index = 0;
    static float acc_buffer_sum = 0.0;
    static uint8_t data_average_over_flag = 0;
    static int16_t zero_passed_num = 0;

    float acc_average = 0.0;
    uint16_t temp = 0;

    temp = sqrt(pow(gyro_data_structure.acc_x, 2) + pow(gyro_data_structure.acc_y, 2) + pow(gyro_data_structure.acc_z, 2));
    acc_filter = temp;

    if (first_flag)
    {
        if (data_in_index < SHAKE_CHECK_DATA_BUFFER_SIZE)
        {
            acc_buffer[data_in_index] = acc_filter;
            if (data_in_index == (SHAKE_CHECK_DATA_BUFFER_SIZE - 1))
            {
                for (uint8_t i = 0; i < SHAKE_CHECK_DATA_BUFFER_SIZE; i++)
                {
                    acc_buffer_sum += acc_buffer[i];
                }
                acc_average = acc_buffer_sum / SHAKE_CHECK_DATA_BUFFER_SIZE;
            }
            data_in_index++;
        }
        else if (data_in_index == SHAKE_CHECK_DATA_BUFFER_SIZE)
        {
            for (uint8_t i = 0; i < SHAKE_CHECK_DATA_BUFFER_SIZE; i++)
            {
                if (i == 0)
                {
                    if (acc_buffer[i] >= acc_average)
                    {
                        data_average_over_flag = true;
                    }
                    else
                    {
                        data_average_over_flag = false;
                    }
                }
                else
                {
                    if (data_average_over_flag == true && (acc_average - acc_buffer[i]) > (gyro_data_structure.acc_earth * SHAKE_STRENGTH_START_CHECK_GAIN))
                    {
                        zero_passed_num++;
                        shake_detect_set_zero_pass_flag_t(i, true);
                        data_average_over_flag = false;
                    }
                    else if (data_average_over_flag == false && (acc_buffer[i] - acc_average) > (gyro_data_structure.acc_earth * SHAKE_STRENGTH_START_CHECK_GAIN))
                    {
                        zero_passed_num++;
                        shake_detect_set_zero_pass_flag_t(i, true);
                        data_average_over_flag = true;
                    }
                    else
                    {
                        shake_detect_set_zero_pass_flag_t(i, false);
                    }
                }
            }
            first_flag = false;
            return 0;
        }
    }

    if (!first_flag)
    {
        if (data_in_index == SHAKE_CHECK_DATA_BUFFER_SIZE)
        {
            data_in_index = 0;
        }
        acc_buffer_sum += (acc_filter - acc_buffer[data_in_index]);
        acc_average = acc_buffer_sum / SHAKE_CHECK_DATA_BUFFER_SIZE;
        acc_buffer[data_in_index] = acc_filter;

        if (shake_detect_get_zero_pass_flag_t(data_in_index) == true)
        {
            zero_passed_num--;
        }

        if (data_average_over_flag == true && (acc_average - acc_buffer[data_in_index]) > (gyro_data_structure.acc_earth * SHAKE_STRENGTH_START_CHECK_GAIN))
        {
            zero_passed_num++;
            shake_detect_set_zero_pass_flag_t(data_in_index, true);
            data_average_over_flag = false;
        }
        else if (data_average_over_flag == false && (acc_buffer[data_in_index] - acc_average) > (gyro_data_structure.acc_earth * SHAKE_STRENGTH_START_CHECK_GAIN))
        {
            zero_passed_num++;
            shake_detect_set_zero_pass_flag_t(data_in_index, true);
            data_average_over_flag = true;
        }
        else
        {
            shake_detect_set_zero_pass_flag_t(data_in_index, false);
        }

        data_in_index++;
    }
    if (zero_passed_num < 0)
    {
        zero_passed_num = 0;
    }
    /* zero_passed_num will be 0 - 20*/
    if (zero_passed_num <= 3)
    {
        gyro_data_structure.shaked_strength = zero_passed_num * SHAKE_STRENGTH_FREQUENCY_GAIN;
    }
    else
    {
        gyro_data_structure.shaked_strength = zero_passed_num * SHAKE_STRENGTH_FREQUENCY_GAIN + acc_average * SHAKE_STRENGTH_ACC_VALUE_GAIN;
    }

    gyro_data_structure.shaked_strength = gyro_data_structure.shaked_strength > 100 ? 100 : gyro_data_structure.shaked_strength;
    if (gyro_data_structure.shaked_strength > SHAKED_THRESHOLD_DEFAULT /* && (acc_filter > gyro_event_info[SHAKE].threshold_value_high || acc_filter < gyro_event_info[SHAKE].threshold_value_low)*/)
    {
        gyro_data_structure.is_shaked = true;
    }
    else
    {
        gyro_data_structure.is_shaked = false;
    }
    return 0;
}

/* for gyro event machanism */
esp_err_t gyro_event_init_t(void)
{
    /* 0 for shake */
    gyro_event_info[SHAKE].event_occured_flag = false;
    gyro_event_info[SHAKE].threshold_value_high = gyro_data_structure.acc_earth * 1.1;
    gyro_event_info[SHAKE].threshold_value_low = gyro_data_structure.acc_earth * 0.9;

    /* 1 for tilt left */
    gyro_event_info[TILT_LEFT].event_occured_flag = false;
    gyro_event_info[TILT_LEFT].threshold_value_high = -gyro_data_structure.acc_earth * TILT_RANGE_GAIN;
    gyro_event_info[TILT_LEFT].threshold_value_low = -gyro_data_structure.acc_earth;

    /* 2 for tilt right */
    gyro_event_info[TILT_RIGHT].event_occured_flag = false;
    gyro_event_info[TILT_RIGHT].threshold_value_high = gyro_data_structure.acc_earth;
    gyro_event_info[TILT_RIGHT].threshold_value_low = gyro_data_structure.acc_earth * TILT_RANGE_GAIN;

    /* 3 for tilt forward */
    gyro_event_info[TILT_FORWARD].event_occured_flag = false;
    gyro_event_info[TILT_FORWARD].threshold_value_high = gyro_data_structure.acc_earth;
    gyro_event_info[TILT_FORWARD].threshold_value_low = gyro_data_structure.acc_earth * ARROW_ORIENTATION_RANGE_GAIN;

    /* 4 for tilt back */
    gyro_event_info[TILT_BACK].event_occured_flag = false;
    gyro_event_info[TILT_BACK].threshold_value_high = -gyro_data_structure.acc_earth * ARROW_ORIENTATION_RANGE_GAIN;
    gyro_event_info[TILT_BACK].threshold_value_low = -gyro_data_structure.acc_earth;

    /* 5 for screen up */
    gyro_event_info[SCREEN_UP].event_occured_flag = false;
    gyro_event_info[SCREEN_UP].threshold_value_high = 0; // no max
    gyro_event_info[SCREEN_UP].threshold_value_low = gyro_data_structure.acc_earth * SCREEN_STATUS_RANGE_GAIN;

    /* 6 for screen down */
    gyro_event_info[SCREEN_DOWN].event_occured_flag = false;
    gyro_event_info[SCREEN_DOWN].threshold_value_high = -gyro_data_structure.acc_earth * SCREEN_STATUS_RANGE_GAIN;
    gyro_event_info[SCREEN_DOWN].threshold_value_low = 0; // no max

    /* 7 for free fall */
    gyro_event_info[FREE_FALL].event_occured_flag = false;
    gyro_event_info[FREE_FALL].threshold_value_high = gyro_data_structure.acc_earth * 0.3;
    gyro_event_info[FREE_FALL].threshold_value_low = -gyro_data_structure.acc_earth * 0.3;

    /* 8 for up_right */
    /* x axis make it sensitive */
    gyro_event_info[UP_RIGHT].event_occured_flag = false;
    gyro_event_info[UP_RIGHT].threshold_value_high = 0;
    gyro_event_info[UP_RIGHT].threshold_value_low = gyro_data_structure.acc_earth * 0.9;

    /* 9 for clockwise rotation, 10 for anticlockwise rotation */
    gyro_event_info[ROTATE_CLOCKWISE].event_occured_flag = false;
    gyro_event_info[ROTATE_CLOCKWISE].threshold_value_high = 50;
    gyro_event_info[ROTATE_CLOCKWISE].threshold_value_low = -50;

    gyro_event_info[ROTATE_ANTICLOCKWISE].event_occured_flag = false;
    gyro_event_info[ROTATE_ANTICLOCKWISE].threshold_value_high = 50;
    gyro_event_info[ROTATE_ANTICLOCKWISE].threshold_value_low = -50;

    return 0;
}

/******************************************************************************
 DEFINE PRIVATE FUNCTIONS
*******************************************************************************/
static esp_err_t gyro_config_t(void)
{
    uint8_t chip_id = 0;
    gyro_data_structure.acc_x = 0;
    gyro_data_structure.acc_y = 0;
    gyro_data_structure.acc_z = 0;
    gyro_data_structure.acc_earth = GRAVITY_DEFAULT_VALUE;
    gyro_data_structure.angle_pitch = 0;
    gyro_data_structure.angle_roll = 0;
    gyro_data_structure.is_shaked = false;
    gyro_data_structure.shaked_strength = 0;
    gyro_data_structure.acc_filter = ACC_FILTER;
#if ACCELEROMETER_QMA6981
    i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, QMA6981_MODE, 0x80);
    i2c_master_read_reg_t(I2C_NUM, SLAVER_ADDRESS, QMA6981_CHIP_ID, &chip_id);
    if (!(chip_id & 0x80))
    {
        i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, QMA6981_RANGE, QMA6981_RANGE_2G);
        i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, QMA6981_SR, 0x2c);
        return -1;
    }
    i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, QMA6981_RANGE, QMA6981_RANGE_2G);
    i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, QMA6981_SR, 0x2c);

#endif

#if GYRO_MPU6887
    i2c_master_read_reg_t(I2C_NUM, SLAVER_ADDRESS, WHO_AM_I, &chip_id);
    if (chip_id != MPU6887_DEVICE_ID)
    {
        return -1;
    }

    /* close the sleep mode */
    i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, PWR_MGMT_1, 0x00);

    /* configurate the digital low pass filter */
    i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, CONFIG, 0x01);
    /* set the gyro scale to 500 deg/s */
    i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, GYRO_CONFIG, 0x08);
    /* set the Sampling Rate   50Hz 49 */
    i2c_master_write_reg_t(I2C_NUM, SLAVER_ADDRESS, SMPLRT_DI, 19);

#endif
    return 0;
}

static float gyro_pitch_angle_range_t(float angle)
{
    /* -180 ~ 180 */
    if (angle > 180)
    {
        return angle - 360;
    }
    else
    {
        return angle;
    }
}

static float gyro_roll_angle_range_t(float angle)
{
    /* -90 ~ 90 */
    if (angle > 90.5 && angle < 269.5)
    {
        return 0;
    }
    else if (angle >= 269.5)
    {
        return angle - 360;
    }
    else
    {
        return angle;
    }
}

/* calculate shake strength */
static void shake_detect_set_zero_pass_flag_t(uint16_t index, bool sta)
{
    uint8_t i, j;
    i = floor(index / 32);
    j = index % 32;
    if (sta == true)
    {
        shake_detect_zero_pass_flags[i] |= 1 << j;
    }
    else
    {
        shake_detect_zero_pass_flags[i] &= (~(1 << j));
    }
}

static bool shake_detect_get_zero_pass_flag_t(uint16_t index)
{
    uint8_t i, j;
    i = floor(index / 32);
    j = index % 32;
    if ((shake_detect_zero_pass_flags[i] & (1 << j)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

static esp_err_t gyro_event_listening_t(float ax, float ay, float az)
{
    // static uint8_t tilt_triggered[5] = {0, 0, 0, 0, 0}; // shake: 0  left: 1 right: 2  forward: 3  back: 4

    /* 0 for shake */
    if (gyro_data_structure.is_shaked == true)
    {
        gyro_event_info[SHAKE].event_occured_flag = true;
    }
    else
    {
        gyro_event_info[SHAKE].event_occured_flag = false;
    }
    /* 1 for tilt left   2 for tilt right */
    if (ax <= gyro_event_info[TILT_LEFT].threshold_value_high && ax >= gyro_event_info[TILT_LEFT].threshold_value_low)
    {
        gyro_event_info[TILT_LEFT].event_occured_flag = true;
        gyro_event_info[TILT_RIGHT].event_occured_flag = false;
    }
    else if (/*ax <= gyro_event_info[TILT_RIGHT].threshold_value_high && */ ax >= gyro_event_info[TILT_RIGHT].threshold_value_low)
    {
        gyro_event_info[TILT_LEFT].event_occured_flag = false;
        gyro_event_info[TILT_RIGHT].event_occured_flag = true;
    }
    else
    {
        gyro_event_info[TILT_LEFT].event_occured_flag = false;
        gyro_event_info[TILT_RIGHT].event_occured_flag = false;
    }

    /* 3 for tilt forward  4 for tilt back */
    if (/* ay <= gyro_event_info[TILT_FORWARD].threshold_value_high && */ ay >= gyro_event_info[TILT_FORWARD].threshold_value_low)
    {
        if (fabs(ay) >= fabs(ax))
        {
            gyro_event_info[TILT_FORWARD].event_occured_flag = true;
            gyro_event_info[TILT_BACK].event_occured_flag = false;
            gyro_event_info[TILT_LEFT].event_occured_flag = false;
            gyro_event_info[TILT_RIGHT].event_occured_flag = false;
        }
        else
        {
            gyro_event_info[TILT_FORWARD].event_occured_flag = false;
            gyro_event_info[TILT_BACK].event_occured_flag = false;
        }
    }
    else if (ay <= gyro_event_info[TILT_BACK].threshold_value_high && ay >= gyro_event_info[TILT_BACK].threshold_value_low)
    {
        if (fabs(ay) >= fabs(ax))
        {
            gyro_event_info[TILT_FORWARD].event_occured_flag = false;
            gyro_event_info[TILT_BACK].event_occured_flag = true;
            gyro_event_info[TILT_LEFT].event_occured_flag = false;
            gyro_event_info[TILT_RIGHT].event_occured_flag = false;
        }
        else
        {
            gyro_event_info[TILT_FORWARD].event_occured_flag = false;
            gyro_event_info[TILT_BACK].event_occured_flag = false;
        }
    }
    else
    {
        gyro_event_info[TILT_FORWARD].event_occured_flag = false;
        gyro_event_info[TILT_BACK].event_occured_flag = false;
    }

    /* 5 for screen up  6 for screen down, 7 for upright check */
    if (az >= gyro_event_info[SCREEN_UP].threshold_value_low)
    {
        gyro_event_info[SCREEN_UP].event_occured_flag = true;
        gyro_event_info[SCREEN_DOWN].event_occured_flag = false;
        gyro_event_info[UP_RIGHT].event_occured_flag = false;
    }
    else if (az <= gyro_event_info[SCREEN_DOWN].threshold_value_high)
    {
        gyro_event_info[SCREEN_UP].event_occured_flag = false;
        gyro_event_info[SCREEN_DOWN].event_occured_flag = true;
        gyro_event_info[UP_RIGHT].event_occured_flag = false;
    }
    else
    {
        gyro_event_info[SCREEN_UP].event_occured_flag = false;
        gyro_event_info[SCREEN_DOWN].event_occured_flag = false;
        if (ax >= gyro_event_info[UP_RIGHT].threshold_value_low)
        {
            gyro_event_info[UP_RIGHT].event_occured_flag = true;
        }
        else
        {
            gyro_event_info[UP_RIGHT].event_occured_flag = false;
        }
    }

    /* 8 for free fall */
    if ((fabs(ax) + fabs(ay) + fabs(az)) >= gyro_event_info[FREE_FALL].threshold_value_low && (fabs(ax) + fabs(ay) + fabs(az)) <= gyro_event_info[FREE_FALL].threshold_value_high)
    {
        gyro_event_info[FREE_FALL].event_occured_flag = true;
    }
    else
    {
        gyro_event_info[FREE_FALL].event_occured_flag = false;
    }

    /* 9 for clockwise rotation, 10 for anticlockwise rotation */
    static float gyro_z = 0;
    gyro_z = gyro_data_structure.gyro_z * 0.2 + gyro_z * 0.8;

    if (az > gyro_data_structure.acc_earth * cos(75))
    {
        if (gyro_z >= gyro_event_info[ROTATE_CLOCKWISE].threshold_value_high)
        {
            gyro_event_info[ROTATE_CLOCKWISE].event_occured_flag = false;
            gyro_event_info[ROTATE_ANTICLOCKWISE].event_occured_flag = true;
        }
        else if (gyro_z <= gyro_event_info[ROTATE_CLOCKWISE].threshold_value_low)
        {
            gyro_event_info[ROTATE_CLOCKWISE].event_occured_flag = true;
            gyro_event_info[ROTATE_ANTICLOCKWISE].event_occured_flag = false;
        }
        else
        {
            gyro_event_info[ROTATE_CLOCKWISE].event_occured_flag = false;
            gyro_event_info[ROTATE_ANTICLOCKWISE].event_occured_flag = false;
        }
    }
    else if (az < -gyro_data_structure.acc_earth * cos(75))
    {
        if (gyro_z >= gyro_event_info[ROTATE_CLOCKWISE].threshold_value_high)
        {
            gyro_event_info[ROTATE_CLOCKWISE].event_occured_flag = true;
            gyro_event_info[ROTATE_ANTICLOCKWISE].event_occured_flag = false;
        }
        else if (gyro_z <= gyro_event_info[ROTATE_CLOCKWISE].threshold_value_low)
        {
            gyro_event_info[ROTATE_CLOCKWISE].event_occured_flag = false;
            gyro_event_info[ROTATE_ANTICLOCKWISE].event_occured_flag = true;
        }
        else
        {
            gyro_event_info[ROTATE_CLOCKWISE].event_occured_flag = false;
            gyro_event_info[ROTATE_ANTICLOCKWISE].event_occured_flag = false;
        }
    }
    else
    {
        gyro_event_info[ROTATE_CLOCKWISE].event_occured_flag = false;
        gyro_event_info[ROTATE_ANTICLOCKWISE].event_occured_flag = false;
    }
    return 0;
}
