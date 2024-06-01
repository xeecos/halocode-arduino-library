#ifndef _MICROPHONE_H_
#define _MICROPHONE_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
#define ES8218E_ADDR 0x10  /*!< 0x11:CE=1;0x10:CE=0*/


/* ES8218E register */

#define ES8218E_RESET              0x00

#define ES8218E_CLOCK_MANAGER1     0x01
#define ES8218E_CLOCK_MANAGER2     0x02
#define ES8218E_CLOCK_MANAGER3     0x03
#define ES8218E_CLOCK_MANAGER4     0x04
#define ES8218E_CLOCK_MANAGER5     0x05
#define ES8218E_CLOCK_MANAGER6     0x06

#define ES8218E_SERIAL_DATA_PORT   0x07

#define ES8218E_SYSTEM_CONTROL1    0x08
#define ES8218E_SYSTEM_CONTROL2    0x09
#define ES8218E_SYSTEM_CONTROL3    0x0a
#define ES8218E_SYSTEM_CONTROL4    0x0b
#define ES8218E_SYSTEM_CONTROL5    0x0c
#define ES8218E_SYSTEM_CONTROL6    0x0d
#define ES8218E_SYSTEM_CONTROL7    0x0e

/* ADC */
#define ES8218E_ADC_CONTROL1       0x0f
#define ES8218E_ADC_CONTROL2       0x10
#define ES8218E_ADCVOLUMEL         0x11
#define ES8218E_ADC_CONTROL4       0x12
#define ES8218E_ADC_CONTROL5       0x13
#define ES8218E_ADC_CONTROL6       0x14
#define ES8218E_ADC_CONTROL7       0x15
#define ES8218E_ADC_CONTROL8       0x16
#define ES8218E_ADC_CONTROL9       0x17
#define ES8218E_ADC_CONTROL10      0x18
#define ES8218E_ADC_CONTROL11      0x19

/* Equalizer to process ADC data. */
#define ES8218E_ADC_CONTROL12      0x1a
#define ES8218E_ADC_CONTROL13      0x1b
#define ES8218E_ADC_CONTROL14      0x1c
#define ES8218E_ADC_CONTROL15      0x1d
#define ES8218E_ADC_CONTROL16      0x1e
#define ES8218E_ADC_CONTROL17      0x1f
#define ES8218E_ADC_CONTROL18      0x20
#define ES8218E_ADC_CONTROL19      0x21
#define ES8218E_ADC_CONTROL20      0x22

typedef enum {
    BIT_LENGTH_MIN = -1,
    BIT_LENGTH_16BITS = 0x03,
    BIT_LENGTH_18BITS = 0x02,
    BIT_LENGTH_20BITS = 0x01,
    BIT_LENGTH_24BITS = 0x00,
    BIT_LENGTH_32BITS = 0x04,
    BIT_LENGTH_MAX,
} es_bits_length_t;

typedef enum {
    MCLK_DIV_MIN = -1,
    MCLK_DIV_1 = 1,
    MCLK_DIV_2 = 2,
    MCLK_DIV_3 = 3,
    MCLK_DIV_4 = 4,
    MCLK_DIV_6 = 5,
    MCLK_DIV_8 = 6,
    MCLK_DIV_9 = 7,
    MCLK_DIV_11 = 8,
    MCLK_DIV_12 = 9,
    MCLK_DIV_16 = 10,
    MCLK_DIV_18 = 11,
    MCLK_DIV_22 = 12,
    MCLK_DIV_24 = 13,
    MCLK_DIV_33 = 14,
    MCLK_DIV_36 = 15,
    MCLK_DIV_44 = 16,
    MCLK_DIV_48 = 17,
    MCLK_DIV_66 = 18,
    MCLK_DIV_72 = 19,
    MCLK_DIV_5 = 20,
    MCLK_DIV_10 = 21,
    MCLK_DIV_15 = 22,
    MCLK_DIV_17 = 23,
    MCLK_DIV_20 = 24,
    MCLK_DIV_25 = 25,
    MCLK_DIV_30 = 26,
    MCLK_DIV_32 = 27,
    MCLK_DIV_34 = 28,
    MCLK_DIV_7  = 29,
    MCLK_DIV_13 = 30,
    MCLK_DIV_14 = 31,
    MCLK_DIV_MAX,
} es_sclk_div_t;

typedef enum {
    LCLK_DIV_MIN = -1,
    LCLK_DIV_128 = 0,
    LCLK_DIV_192 = 1,
    LCLK_DIV_256 = 2,
    LCLK_DIV_384 = 3,
    LCLK_DIV_512 = 4,
    LCLK_DIV_576 = 5,
    LCLK_DIV_768 = 6,
    LCLK_DIV_1024 = 7,
    LCLK_DIV_1152 = 8,
    LCLK_DIV_1408 = 9,
    LCLK_DIV_1536 = 10,
    LCLK_DIV_2112 = 11,
    LCLK_DIV_2304 = 12,

    LCLK_DIV_125 = 16,
    LCLK_DIV_136 = 17,
    LCLK_DIV_250 = 18,
    LCLK_DIV_272 = 19,
    LCLK_DIV_375 = 20,
    LCLK_DIV_500 = 21,
    LCLK_DIV_544 = 22,
    LCLK_DIV_750 = 23,
    LCLK_DIV_1000 = 24,
    LCLK_DIV_1088 = 25,
    LCLK_DIV_1496 = 26,
    LCLK_DIV_1500 = 27,
    LCLK_DIV_MAX,
} es_lclk_div_t;

typedef enum {
    D2SE_PGA_GAIN_MIN = -1,
    D2SE_PGA_GAIN_DIS = 0,
    D2SE_PGA_GAIN_EN = 1,
    D2SE_PGA_GAIN_MAX =2,
} es_d2se_pga_t;

typedef enum {
    ADC_INPUT_MIN = -1,
    ADC_INPUT_LINPUT1_RINPUT1 = 0x00,
    ADC_INPUT_MIC1  = 0x05,
    ADC_INPUT_MIC2  = 0x06,
    ADC_INPUT_LINPUT2_RINPUT2 = 0x50,
    ADC_INPUT_DIFFERENCE = 0xf0,
    ADC_INPUT_MAX,
} es_adc_input_t;

typedef enum {
    DAC_OUTPUT_MIN = -1,
    DAC_OUTPUT_LOUT1 = 0x04,
    DAC_OUTPUT_LOUT2 = 0x08,
    DAC_OUTPUT_SPK   = 0x09,
    DAC_OUTPUT_ROUT1 = 0x10,
    DAC_OUTPUT_ROUT2 = 0x20,
    DAC_OUTPUT_ALL = 0x3c,
    DAC_OUTPUT_MAX,
} es_dac_output_t;

typedef enum {
    MIC_GAIN_MIN = -1,
    MIC_GAIN_0DB = 0,
    MIC_GAIN_3DB = 3,
    MIC_GAIN_6DB = 6,
    MIC_GAIN_9DB = 9,
    MIC_GAIN_12DB = 12,
    MIC_GAIN_15DB = 15,
    MIC_GAIN_18DB = 18,
    MIC_GAIN_21DB = 21,
    MIC_GAIN_24DB = 24,
    MIC_GAIN_MAX,
} es_mic_gain_t;

typedef enum {
    ES_MODULE_MIN = -1,
    ES_MODULE_ADC = 0x01,
    ES_MODULE_DAC = 0x02,
    ES_MODULE_ADC_DAC = 0x03,
    ES_MODULE_LINE = 0x04,
    ES_MODULE_MAX
} es_module_t;

typedef enum {
    ES_MODE_MIN = -1,
    ES_MODE_SLAVE = 0x00,
    ES_MODE_MASTER = 0x01,
    ES_MODE_MAX,
} es_mode_t;

typedef enum {
    ES_I2S_MIN = -1,
    ES_I2S_NORMAL = 0,
    ES_I2S_LEFT = 1,
    ES_I2S_RIGHT = 2,
    ES_I2S_DSP = 3,
    ES_I2S_MAX
} es_i2s_fmt_t;

/**
 * @brief Configure ES8388 clock
 */
typedef struct {
    es_sclk_div_t sclk_div;    /*!< bits clock divide */
    es_lclk_div_t lclk_div;    /*!< WS clock divide */
} es_i2s_clock_t;


extern void microphone_init_t();
extern void microphone_update_t(int loudness);
extern int microphone_loudness();
extern void es8218e_config_fmt(es_i2s_fmt_t cfg);
extern void es8218e_start(void);
extern void es8218e_stop(void);
extern void es8218e_read_all();

#ifdef __cplusplus
}
#endif
#endif