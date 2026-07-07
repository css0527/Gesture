#include "debug.h"
#include "hardware.h"
#include "ch32h417_usbss_device.h"
#include "dvp.h"           // 添加 DVP 头文件
#include "uvclib.h"        // 添加 UVC 头文件
#include "ch32h417_hsem.h" // 添加HSEM头文件
#include "ch32h417_pwr.h"  // 添加PWR头文件

// 共享图像缓冲区指针
extern uint8_t* Dvp_Recaddr;  // 来自 uvc.c

// 定义手势识别结果存储位置（在共享内存中）
#define GESTURE_RESULT_ADDR   0x200C8000
#define GESTURE_CONFIDENCE_ADDR 0x200C8004

// 手势识别相关定义
#define GESTURE_FIST          0    // 拳头
#define GESTURE_PALM          1    // 手掌
#define GESTURE_SWIPE_LEFT    2    // 左滑
#define GESTURE_SWIPE_RIGHT   3    // 右滑
#define GESTURE_SWIPE_UP      4    // 上滑
#define GESTURE_SWIPE_DOWN    5    // 下滑
#define GESTURE_PINCH         6    // 捏合
#define GESTURE_OK            7    // OK手势
#define GESTURE_NONE          8    // 无手势

// 全局变量
uint8_t gesture_result = GESTURE_NONE;  // 当前手势识别结果
float gesture_confidence = 0.0f;        // 当前手势置信度

// 存储手势识别结果到共享内存
void Store_Gesture_Result(uint8_t gesture, float confidence)
{
    volatile uint8_t* gesture_ptr = (volatile uint8_t*)GESTURE_RESULT_ADDR;
    volatile float* confidence_ptr = (volatile float*)GESTURE_CONFIDENCE_ADDR;
    
    *gesture_ptr = gesture;
    *confidence_ptr = confidence;
}

// V3F作为主核，负责UVC视频流处理和协调V5F
int main(void)
{
    SystemInit();
    SystemAndCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);
    
    printf("V3F UVC Processing Core Started\r\n");
    printf("SystemCoreClk:%d\r\n", SystemCoreClock);
    
    // 根据运行模式进行不同的初始化
    #if (Run_Core == Run_Core_V3FandV5F)
        // 在双核模式下，V3F作为主核唤醒V5F并进入STOP模式等待同步
        printf("Initializing dual-core mode (V3F main, V5F slave)...\r\n");
        
        
        
        // 唤醒V5F从核
        printf("Waking up V5F core...\r\n");
        NVIC_WakeUp_V5F(Core_V5F_StartAddr);
        
        // 配置HSEM中断
        HSEM_ITConfig(HSEM_ID0, ENABLE);
        
        // 配置NVIC
        NVIC->SCTLR |= 1<<4;
        
        // 使能PWR时钟
        RCC_HB1PeriphClockCmd(RCC_HB1Periph_PWR, ENABLE);
        
        // 进入STOP模式等待V5F同步（使用WFE唤醒）
        printf("V3F entering STOP mode, waiting for sync...\r\n");
        PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFE);
        
        // V3F被唤醒后继续执行
        printf("V3F wake up, continuing execution...\r\n");
        
        // 清除HSEM标志
        HSEM_ClearFlag(HSEM_ID0);
        // 硬件初始化（摄像头等）
        Hardware();
        printf("Dual-core synchronization completed.\r\n");

    #elif (Run_Core == Run_Core_V3F)
        // 单V3F模式
        printf("Initializing single V3F mode...\r\n");
        Hardware();

    #elif (Run_Core == Run_Core_V5F)
        // 这种情况不应该发生，因为V3F是主核
        printf("Warning: V3F configured as V5F mode - this is incorrect!\r\n");
        // 唤醒V5F并进入STOP模式
        NVIC_WakeUp_V5F(Core_V5F_StartAddr);
        PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFE);
        printf("V3F wake up\r\n");
    #endif
    
    printf("Starting UVC video stream and gesture recognition processing...\r\n");
    
    // 初始化手势识别结果
    Store_Gesture_Result(GESTURE_NONE, 0.0f);
    
    // UVC主循环，处理视频流并进行手势识别
    while(1) {
        // UVC视频流处理
        // 这里会处理来自摄像头的视频数据
        
        // 模拟手势识别过程（实际应用中这里会调用TFLM进行推理）
        // 注意：在实际实现中，这通常需要在V3F上运行TFLM或通过某种方式将图像数据传给V5F进行推理
        // 由于V3F资源限制，我们这里模拟手势识别结果
        
        // 实际的图像处理和手势识别逻辑会在这里
        // 从Dvp_Recaddr获取图像数据，然后进行预处理和推理
        if(Dvp_Recaddr != NULL) {
            // 处理从DVP接收到的图像数据
            // 这里应该调用手势识别算法
            
            // 模拟手势识别结果（实际应用中应该由TFLM推理得到）
            // 在真实应用中，这里需要：
            // 1. 将图像数据预处理成模型输入格式
            // 2. 调用TFLM模型进行推理
            // 3. 获取推理结果和置信度
            
            // 为了演示目的，我们随机生成一些手势结果
            static uint32_t gesture_counter = 0;
            gesture_counter++;
            
            if(gesture_counter % 100 == 0) { // 每100个循环模拟一个手势
                uint8_t simulated_gesture = (gesture_counter / 100) % 8; // 0-7对应不同手势
                float simulated_confidence = 0.85f; // 模拟高置信度
                
                // 存储识别结果到共享内存供V5F读取
                Store_Gesture_Result(simulated_gesture, simulated_confidence);
                
                // 打印识别结果
                const char* gesture_names[] = {
                    "FIST", "PALM", "SWIPE_LEFT", "SWIPE_RIGHT", 
                    "SWIPE_UP", "SWIPE_DOWN", "PINCH", "OK", "NONE"
                };
                
                printf("Gesture recognized: %s, Confidence: %.2f\r\n", 
                       gesture_names[simulated_gesture], simulated_confidence);
            }
        }
        
        // 添加短延时避免CPU占用过高
        Delay_Ms(10);
    }
}
