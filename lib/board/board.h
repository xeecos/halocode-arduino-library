#ifndef _BOARD_H_
#define _BOARD_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
    union
    {
        uint8_t byteVal[2];
        int16_t shortVal;
    }val2byte;
    extern void board_init();

#ifdef __cplusplus
}
#endif
#endif