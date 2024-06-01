#ifndef _LED_MATRIX_H_
#define _LED_MATRIX_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
    #define USE_DRIVER_SLED173x        (0x00)
    typedef enum
    {
        COLOR_WHITE = 0,
        COLOR_PURPLE,
        COLOR_RED,
        COLOR_ORANGE,
        COLOR_YELLOW,
        COLOR_GREEN,
        COLOR_CYAN,
        COLOR_BLUE,
        COLOR_PINK,
        COLOR_BLACK,
        COLOR_GOLD
    }color_type_t;

    extern void led_matrix_set_driver_t(int driver_id);
    extern void led_matrix_init_t(void);
    extern void led_matrix_update(void);
    extern void led_matrix_clear(void);
    extern void led_matrix_get_all_led_info_t(uint8_t *data, int len);
    extern void led_matrix_set_all_led_info_t(uint8_t *data, int len);
    extern void led_matrix_set_single_led(uint8_t led_id, uint8_t red, uint8_t green, uint8_t blue);
    extern void led_matrix_set_all_led(uint8_t red, uint8_t green, uint8_t blue);
    extern void led_matrix_set_colorful_led(uint8_t* data, int len, int offset);
    extern void led_matrix_is_updated_t(bool *sta);
#ifdef __cplusplus
}
#endif

#endif
