#ifndef SLED173X_DRIVER_H_
#define SLED173X_DRIVER_H_
#ifdef __cplusplus
extern "C" {
#endif
extern esp_err_t sled173x_led_update_all_t(uint8_t *data, uint16_t len);
extern esp_err_t sled173x_type4_config_t(void);
#ifdef __cplusplus
}
#endif
#endif /* SLED173X_DRIVER_H_ */ 