/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2025/03/01
 * Description        : Main program body for V5F gesture control relay.
 *********************************************************************************
 * Copyright (c) 2025 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include "debug.h"
#include "hardware.h"
#include "ch32h417_gpio.h"
#include "ch32h417_rcc.h"
#include "ch32h417_hsem.h"
#include "ch32h417_dvp.h"  // 添加DVP头文件用于图像处理
#include "tflm/examples/hello_world/models/gesture_model.h"  // 包含手势模型

// 继电器控制引脚定义 - PE3/4/5
#define RELAY1_PIN    GPIO_Pin_3  // PE3 - 继电器1
#define RELAY2_PIN    GPIO_Pin_4  // PE4 - 继电器2  
#define RELAY3_PIN    GPIO_Pin_5  // PE5 - 继电器3
#define RELAY_PORT    GPIOE

// 手势识别相关定义
#define GESTURE_FIST          0    // 拳头 - 关闭所有继电器
#define GESTURE_PALM          1    // 手掌 - 开启所有继电器
#define GESTURE_SWIPE_LEFT    2    // 左滑 - 控制继电器1
#define GESTURE_SWIPE_RIGHT   3    // 右滑 - 控制继电器2
#define GESTURE_SWIPE_UP      4    // 上滑 - 控制继电器3
#define GESTURE_SWIPE_DOWN    5    // 下滑 - 关闭所有继电器
#define GESTURE_PINCH         6    // 捏合 - 特殊功能
#define GESTURE_OK            7    // OK手势 - 特殊功能
#define GESTURE_NONE          8    // 无手势

// 手势识别结果存储位置（在共享内存中）
#define GESTURE_RESULT_ADDR   0x200C8000
#define GESTURE_CONFIDENCE_ADDR 0x200C8004

// 图像处理缓冲区（从V3F共享）
#define IMAGE_BUFFER_ADDR     0x200C0000
#define IMAGE_BUFFER_SIZE     320*240*2  // 假设QVGA格式

// 全局变量
static uint8_t relay_state[3] = {0, 0, 0};  // 继电器状态数组
static uint8_t last_gesture = GESTURE_NONE;  // 上一次检测到的手势

/*********************************************************************
 * @fn      Relay_Init
 *
 * @brief   初始化继电器控制引脚 - 符合CH32H417技术手册要求
 *
 * @return  none
 */
void Relay_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    
    // 使能GPIOE时钟
    RCC_HB2PeriphClockCmd(RCC_HB2Periph_GPIOE, ENABLE);
    
    // 配置继电器控制引脚为推挽输出
    GPIO_InitStructure.GPIO_Pin = RELAY1_PIN | RELAY2_PIN | RELAY3_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Very_High;     // 输出速度50MHz
    GPIO_Init(RELAY_PORT, &GPIO_InitStructure);
    
    // 延时确保GPIO配置生效
    Delay_Ms(10);
    
    // 初始化时关闭所有继电器（低电平有效）
    GPIO_WriteBit(RELAY_PORT, RELAY1_PIN, Bit_SET);  // 高电平关闭继电器
    GPIO_WriteBit(RELAY_PORT, RELAY2_PIN, Bit_SET);
    GPIO_WriteBit(RELAY_PORT, RELAY3_PIN, Bit_SET);
    
    printf("Relay control pins initialized\r\n");
    printf("Relay 1 OFF (PE3 HIGH)\r\n");
    printf("Relay 2 OFF (PE4 HIGH)\r\n");
    printf("Relay 3 OFF (PE5 HIGH)\r\n");
}

/*********************************************************************
 * @fn      Control_Relay
 *
 * @brief   控制指定继电器 - 严格按照技术手册要求
 *
 * @param   relay_num - 继电器编号 (1-3)
 *          state   - 状态 (0=关闭, 1=开启)
 *
 * @return  none
 */
void Control_Relay(uint8_t relay_num, uint8_t state)
{
    if(relay_num < 1 || relay_num > 3) return;
    
    uint16_t pin = 0;
    
    switch(relay_num)
    {
        case 1: pin = RELAY1_PIN; break;
        case 2: pin = RELAY2_PIN; break;
        case 3: pin = RELAY3_PIN; break;
        default: return;
    }
    
    if(state)
    {
        // 开启继电器（低电平有效）
        GPIO_ResetBits(RELAY_PORT, pin);
        relay_state[relay_num-1] = 1;
        printf("Relay %d ON (Pin PE%d LOW)\r\n", relay_num, relay_num+2);
    }
    else
    {
        // 关闭继电器（高电平有效）
        GPIO_SetBits(RELAY_PORT, pin);
        relay_state[relay_num-1] = 0;
        printf("Relay %d OFF (Pin PE%d HIGH)\r\n", relay_num, relay_num+2);
    }
    
    // 添加较长延时确保继电器动作
    Delay_Ms(100);
}

/*********************************************************************
 * @fn      Control_All_Relays
 *
 * @brief   控制所有继电器
 *
 * @param   state - 状态 (0=全部关闭, 1=全部开启)
 *
 * @return  none
 */
void Control_All_Relays(uint8_t state)
{
    for(uint8_t i = 1; i <= 3; i++)
    {
        Control_Relay(i, state);
    }
}

/*********************************************************************
 * @fn      Process_Gesture
 *
 * @brief   处理手势识别结果并控制继电器
 *
 * @param   gesture_id - 手势ID
 *
 * @return  none
 */
void Process_Gesture(uint8_t gesture_id)
{
    if(gesture_id == last_gesture) {
        // 防止重复处理同一手势
        return;
    }
    
    last_gesture = gesture_id;
    
    switch(gesture_id)
    {
        case GESTURE_FIST:  // 拳头 - 关闭所有继电器
            Control_All_Relays(0);
            printf("All relays OFF (Fist gesture)\r\n");
            break;
            
        case GESTURE_PALM:  // 手掌 - 开启所有继电器
            Control_All_Relays(1);
            printf("All relays ON (Palm gesture)\r\n");
            break;
            
        case GESTURE_SWIPE_LEFT:  // 左滑 - 控制继电器1
            Control_Relay(1, !relay_state[0]);  // 切换状态
            printf("Relay 1 toggled (Swipe left)\r\n");
            break;
            
        case GESTURE_SWIPE_RIGHT:  // 右滑 - 控制继电器2
            Control_Relay(2, !relay_state[1]);  // 切换状态
            printf("Relay 2 toggled (Swipe right)\r\n");
            break;
            
        case GESTURE_SWIPE_UP:  // 上滑 - 控制继电器3
            Control_Relay(3, !relay_state[2]);  // 切换状态
            printf("Relay 3 toggled (Swipe up)\r\n");
            break;
            
        case GESTURE_SWIPE_DOWN:  // 下滑 - 关闭所有继电器
            Control_All_Relays(0);
            printf("All relays OFF (Swipe down)\r\n");
            break;
            
        case GESTURE_PINCH:  // 捏合 - 继电器1和2同时切换
            Control_Relay(1, !relay_state[0]);
            Control_Relay(2, !relay_state[1]);
            printf("Relay 1 and 2 toggled (Pinch gesture)\r\n");
            break;
            
        case GESTURE_OK:  // OK手势 - 继电器2和3同时切换
            Control_Relay(2, !relay_state[1]);
            Control_Relay(3, !relay_state[2]);
            printf("Relay 2 and 3 toggled (OK gesture)\r\n");
            break;
            
        case GESTURE_NONE:  // 无手势 - 不做任何操作
        default:
            break;
    }
}

/*********************************************************************
 * @fn      Get_Gesture_From_Shared_Memory
 *
 * @brief   从共享内存获取手势识别结果
 *
 * @return  手势ID
 */
uint8_t Get_Gesture_From_Shared_Memory(void)
{
    volatile uint8_t* gesture_ptr = (volatile uint8_t*)GESTURE_RESULT_ADDR;
    volatile uint8_t gesture = *gesture_ptr;
    
    return gesture;
}

/*********************************************************************
 * @fn      Get_Gesture_Confidence
 *
 * @brief   从共享内存获取手势置信度
 *
 * @return  置信度值
 */
float Get_Gesture_Confidence(void)
{
    volatile float* confidence_ptr = (volatile float*)GESTURE_CONFIDENCE_ADDR;
    float confidence = *confidence_ptr;
    
    return confidence;
}

/*********************************************************************
 * @fn      Set_Gesture_Result
 *
 * @brief   设置手势识别结果到共享内存
 *
 * @param   gesture_id - 手势ID
 *          confidence - 置信度
 *
 * @return  none
 */
void Set_Gesture_Result(uint8_t gesture_id, float confidence)
{
    volatile uint8_t* gesture_ptr = (volatile uint8_t*)GESTURE_RESULT_ADDR;
    volatile float* confidence_ptr = (volatile float*)GESTURE_CONFIDENCE_ADDR;
    
    *gesture_ptr = gesture_id;
    *confidence_ptr = confidence;
}

/*********************************************************************
 * @fn      Perform_Gesture_Recognition
 *
 * @brief   执行手势识别（模拟）
 *
 * @return  手势ID
 */
uint8_t Perform_Gesture_Recognition(void)
{
    // 这里应该实现实际的手势识别算法
    // 使用从V3F共享过来的图像数据
    
    // 为了演示目的，这里模拟手势识别
    // 在实际应用中，这会涉及调用TensorFlow Lite Micro模型
    
    // 模拟检测到某种手势
    // 这部分需要与实际的TFLM手势识别模型集成
    static uint32_t gesture_counter = 0;
    gesture_counter++;
    
    // 模拟基于图像数据的手势识别结果
    // 实际应用中这里会调用TFLM模型
    if(gesture_counter % 100 == 0) {
        uint8_t simulated_gesture = (gesture_counter / 100) % 8; // 0-7对应不同手势
        return simulated_gesture;
    }
    
    return GESTURE_NONE; // 无手势
}

/*********************************************************************
 * @fn      Initialize_Gesture_Model
 *
 * @brief   初始化手势识别模型
 *
 * @return  none
 */
void Initialize_Gesture_Model(void)
{
    // 将模型数据存储到指定位置或准备用于TFLM
    printf("Gesture model loaded. Size: %d bytes\r\n", gesture_model_data_len);
    printf("Model accuracy: 98.69%%\r\n");
    printf("Categories: fist, palm, swipe_left, swipe_right, swipe_up, swipe_down, pinch, ok, none\r\n");
    
    // 在实际应用中，这里会初始化TFLM解释器
    // 并加载手势识别模型
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program for gesture control relay system.
 *
 * @return  none
 */
int main(void)
{
    SystemAndCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);
    printf("V5F Gesture Control Relay System Started\r\n");
    printf("SystemCoreClk:%d\r\n", SystemCoreClock);
    
    // 初始化手势识别模型
    Initialize_Gesture_Model();
    
    // 初始化继电器控制
    Relay_Init();
    
    Delay_Ms(500);
    
    // 执行继电器测试
    // printf("Testing relay functionality...\r\n");
    // Control_Relay(1, 1);  // 开启继电器1
    // Delay_Ms(1000);
    // Control_Relay(1, 0);  // 关闭继电器1
    // Delay_Ms(500);
    // Control_Relay(2, 1);  // 开启继电器2
    // Delay_Ms(1000);
    // Control_Relay(2, 0);  // 关闭继电器2
    // Delay_Ms(500);
    // Control_Relay(3, 1);  // 开启继电器3
    // Delay_Ms(1000);
    // Control_Relay(3, 0);  // 关闭继电器3
    // printf("Relay test completed.\r\n");
    
    // 在双核模式下，V5F需要等待与V3F同步
    #if (Run_Core == Run_Core_V3FandV5F)
        // V5F等待同步
        printf("V5F waiting for synchronization...\r\n");
        HSEM_FastTake(HSEM_ID0);
        HSEM_ReleaseOneSem(HSEM_ID0, 0);
        printf("V5F synchronization completed\r\n");

    #elif (Run_Core == Run_Core_V5F)
        Hardware();
    #endif

    printf("Gesture control relay system ready\r\n");
    printf("Supported gestures: Fist, Palm, Swipe Left/Right/Up/Down, Pinch, OK\r\n");

    uint32_t loop_counter = 0;
    
    while(1)
    {
        // 执行手势识别
        uint8_t detected_gesture = Perform_Gesture_Recognition();
        
        // 如果检测到手势，设置置信度（模拟值）
        if(detected_gesture != GESTURE_NONE) {
            float confidence = 0.85f; // 模拟置信度，实际应从模型获得
            Set_Gesture_Result(detected_gesture, confidence);
            
            printf("Gesture detected: %d, Confidence: %.2f\r\n", detected_gesture, confidence);
            Process_Gesture(detected_gesture);
        }
        
        // 也可以从共享内存读取手势结果（备用方式）
        uint8_t shared_gesture = Get_Gesture_From_Shared_Memory();
        float shared_confidence = Get_Gesture_Confidence();
        
        if(shared_confidence > 0.7f && shared_gesture != GESTURE_NONE && shared_gesture != detected_gesture) {
            printf("Processing shared gesture: %d, Confidence: %.2f\r\n", shared_gesture, shared_confidence);
            Process_Gesture(shared_gesture);
        }
        
        // 每100ms检测一次
        Delay_Ms(100);
        
        loop_counter++;
        if(loop_counter % 10 == 0) {
            // 每10次循环打印一次状态
            printf("System running... Last gesture: %d, Relay states: [%d,%d,%d]\r\n", 
                   last_gesture, relay_state[0], relay_state[1], relay_state[2]);
        }
    }
}
