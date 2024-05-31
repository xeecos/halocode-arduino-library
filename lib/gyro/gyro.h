#ifndef _GYRO_H_
#define _GYRO_H_
#include "esp_err.h"
#include <stdint.h>
#ifdef __cplusplus
extern "C"
{
#endif
    typedef enum
    {
        SHAKE = 0,
        TILT_LEFT,
        TILT_RIGHT,
        TILT_FORWARD,
        TILT_BACK,
        SCREEN_UP,
        SCREEN_DOWN,
        UP_RIGHT,
        FREE_FALL,
        ROTATE_CLOCKWISE,
        ROTATE_ANTICLOCKWISE,
        EVENT_MAX
    } gyro_event_type_t;

    typedef enum
    {
        AXIS_ID_X = 1,
        AXIS_ID_Y,
        AXIS_ID_Z,
        AXIS_ID_MAX
    } gyro_acc_id_t;

    typedef enum
    {
        ANGLE_ID_PITCH = 1,
        ANGLE_ID_ROLL,
        ANGLE_ID_YAW,
        ANGLE_ID_MAX
    } gyro_angle_id_t;

    extern esp_err_t gyro_get_acc_x_t(float *out_val);
    extern esp_err_t gyro_get_acc_y_t(float *out_val);
    extern esp_err_t gyro_get_acc_z_t(float *out_val);
    extern esp_err_t gyro_get_acc_t(float *out_val, uint8_t axis);

    extern esp_err_t gyro_get_gyro_x_t(float *out_val);
    extern esp_err_t gyro_get_gyro_y_t(float *out_val);
    extern esp_err_t gyro_get_gyro_z_t(float *out_val);
    extern esp_err_t gyro_get_gyro_t(float *out_val, uint8_t axis);

    extern esp_err_t gyro_get_rotate_angle_x_t(float *out_val);
    extern esp_err_t gyro_get_rotate_angle_y_t(float *out_val);
    extern esp_err_t gyro_get_rotate_angle_z_t(float *out_val);
    extern esp_err_t gyro_get_rotate_angle_t(float *out_val, uint8_t axis);
    extern esp_err_t gyro_reset_rotate_angle_t(uint8_t axis);

    extern esp_err_t gyro_get_shaked_strength_t(float *out_val);
    extern esp_err_t gyro_set_shaked_threshold_t(float value);
    extern esp_err_t gyro_is_shaked_t(bool *out_sta);
    extern esp_err_t gyro_get_pitch_angle_t(float *out_val);
    extern esp_err_t gyro_get_roll_angle_t(float *out_val);
    extern esp_err_t gyro_get_yaw_angle_t(float *out_val);

    extern esp_err_t gyro_get_all_tilt_status_t(uint16_t *out_sta);
    extern esp_err_t gyro_get_tilt_status_t(uint16_t tilt_id, uint16_t *out_sta);
    extern esp_err_t gyro_init_t(void);
    extern esp_err_t gyro_deinit_t(void);
    extern esp_err_t gyro_acc_update_t(void);
    extern esp_err_t gyro_calibrate_t(void);
    extern esp_err_t gyro_update_t(void);
    extern esp_err_t gyro_test_t(void);

    extern esp_err_t gyro_shake_detect_t(void);
    extern esp_err_t gyro_event_init_t(void);
#ifdef __cplusplus
}
#endif
#endif /* _GYRO_H_ */
