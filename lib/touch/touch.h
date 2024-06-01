#ifndef _TOUCH_H_
#define _TOUCH_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
extern void touch_init_t();
extern int touch_status(int key);
#ifdef __cplusplus
}
#endif
#endif