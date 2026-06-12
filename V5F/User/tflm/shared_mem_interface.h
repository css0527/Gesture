#ifndef __SHARED_MEM_INTERFACE_H
#define __SHARED_MEM_INTERFACE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// 共享内存地址（需要与V3F保持一致）
#define SHARED_MEM_BASE     0x20140000
#define IMAGE_WIDTH         320
#define IMAGE_HEIGHT        240
#define IMAGE_BUFFER_SIZE   (IMAGE_WIDTH * IMAGE_HEIGHT * 2)

#define IMAGE_BUFFER_ADDR   (SHARED_MEM_BASE)
#define SYNC_FLAG_ADDR       (SHARED_MEM_BASE + IMAGE_BUFFER_SIZE)

#define SYNC_IDLE           0
#define SYNC_IMAGE_READY    1
#define SYNC_RESULT_READY   2

// 初始化共享内存接口
void shared_mem_init(void);

// 等待新图像并获取
int shared_mem_wait_for_image(uint16_t* buffer, int max_size);

// 发送推理结果
void shared_mem_send_result(int gesture_id, float confidence);

#ifdef __cplusplus
}
#endif

#endif
