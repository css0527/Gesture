#include "shared_mem_interface.h"
#include "debug.h"

static volatile uint8_t* sync_flag = (volatile uint8_t*)SYNC_FLAG_ADDR;
static volatile uint16_t* image_buffer = (volatile uint16_t*)IMAGE_BUFFER_ADDR;

void shared_mem_init(void) {
    *sync_flag = SYNC_IDLE;
    printf("Shared memory initialized at 0x%08X\r\n", SHARED_MEM_BASE);
}

int shared_mem_wait_for_image(uint16_t* buffer, int max_size) {
    // 等待V3F通知有新图像
    while (*sync_flag != SYNC_IMAGE_READY) {
        __WFI();  // 等待中断
    }
    
    // 复制图像数据
    int copy_size = (max_size < IMAGE_WIDTH * IMAGE_HEIGHT) ? 
                    max_size : IMAGE_WIDTH * IMAGE_HEIGHT;
    for (int i = 0; i < copy_size; i++) {
        buffer[i] = image_buffer[i];
    }
    
    return copy_size;
}

void shared_mem_send_result(int gesture_id, float confidence) {
    // 将结果写入共享内存
    volatile float* result_addr = (volatile float*)(SYNC_FLAG_ADDR + 4);
    result_addr[0] = confidence;
    volatile int* id_addr = (volatile int*)(SYNC_FLAG_ADDR + 8);
    *id_addr = gesture_id;
    
    // 通知V3F结果已就绪
    *sync_flag = SYNC_RESULT_READY;
}
