#include "debug.h"
#include "hardware.h"
#include "ch32h417_usbss_device.h"
#include "dvp.h"           // 添加 DVP 头文件
#include "uvclib.h"        // 添加 UVC 头文件

// 共享图像缓冲区指针
extern uint8_t* Dvp_Recaddr;  // 来自 uvc.c

// V3F只负责UVC视频流处理
int main(void)
{
    SystemInit();
    SystemAndCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);
    
    printf("V3F UVC Processing Core Started\r\n");
    
    // 初始化UVC和摄像头
    Hardware();
    
    // 唤醒V5F
    NVIC_WakeUp_V5F(Core_V5F_StartAddr);
    
    // UVC主循环，不参与TFLM推理
    while(1) {
        // UVC视频流处理
        // 将处理后的数据放入共享内存
    }
}
