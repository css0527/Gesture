#ifndef __IPC_COMM_H
#define __IPC_COMM_H

#include "ch32h417.h"

/* IPC Channel定义 */
#define IPC_CH_GESTURE_DATA    0   /* V3F -> V5F 手势图像数据 */
#define IPC_CH_INFERENCE_RESULT 1  /* V5F -> V3F 推理结果 */

/* 共享内存地址定义 (需要在链接脚本中预留) */
#define SHARED_MEM_BASE        0x200C0000  /* 共享内存基地址 */
#define GESTURE_DATA_ADDR      (SHARED_MEM_BASE)
#define GESTURE_DATA_SIZE      (128 * 128 * 2)  /* 128x128 RGB565 */

/* 手势识别结果结构 */
typedef struct {
    uint8_t gesture_id;      /* 手势ID */
    float confidence;        /* 置信度 */
    uint32_t timestamp;      /* 时间戳 */
} gesture_result_t;

/* 初始化IPC通信 */
void IPC_Init(void);

/* V3F发送手势数据到V5F */
void IPC_SendGestureData(uint8_t* data, uint32_t size);

/* V5F接收手势数据 */
uint32_t IPC_ReceiveGestureData(uint8_t* buffer, uint32_t max_size);

/* V5F发送推理结果到V3F */
void IPC_SendResult(gesture_result_t* result);

/* V3F接收推理结果 */
uint32_t IPC_ReceiveResult(gesture_result_t* result);

#endif
