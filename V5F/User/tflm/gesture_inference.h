#ifndef __GESTURE_INFERENCE_H
#define __GESTURE_INFERENCE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int gesture_inference_init(void);
int gesture_inference_run(uint16_t* image, int width, int height,
                          int* gesture_id, float* confidence);
const char* gesture_inference_get_name(int gesture_id);

#ifdef __cplusplus
}
#endif

#endif
