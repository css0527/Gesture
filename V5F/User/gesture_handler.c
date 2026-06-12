/********************************** (C) COPYRIGHT *******************************
 * File Name          : gesture_handler.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2025/03/01
 * Description        : Gesture processing and relay control handler.
 *********************************************************************************
 * Copyright (c) 2025 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include "debug.h"
#include "ch32h417_gpio.h"
#include "ch32h417_rcc.h"

// 继电器控制引脚定义
#define RELAY1_PIN    GPIO_Pin_3  // PE3 - 继电器1
#define RELAY2_PIN    GPIO_Pin_4  // PE4 - 继电器2  
#define RELAY3_PIN    GPIO_Pin_5  // PE5 - 继电器3
#define RELAY_PORT    GPIOE

// 手势定义
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
extern uint8_t relay_state[3];  // 外部声明的继电器状态数组

/*********************************************************************
 * @fn      Gesture_Relay_Init
 *
 * @brief   初始化手势控制继电器系统
 *
 * @return  none
 */
void Gesture_Relay_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    
    // 使能GPIOE时钟
    RCC_HB2PeriphClockCmd(RCC_HB2Periph_GPIOE, ENABLE);
    
    // 配置继电器控制引脚为推挽输出
    GPIO_InitStructure.GPIO_Pin = RELAY1_PIN | RELAY2_PIN | RELAY3_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Very_High;
    GPIO_Init(RELAY_PORT, &GPIO_InitStructure);
    
    // 初始化时关闭所有继电器（低电平有效）
    GPIO_WriteBit(RELAY_PORT, RELAY1_PIN, Bit_SET);
    GPIO_WriteBit(RELAY_PORT, RELAY2_PIN, Bit_SET);
    GPIO_WriteBit(RELAY_PORT, RELAY3_PIN, Bit_SET);
    
    printf("Gesture relay control system initialized\r\n");
}

/*********************************************************************
 * @fn      Handle_Gesture_Command
 *
 * @brief   根据手势命令控制继电器
 *
 * @param   gesture_id - 手势ID
 *          confidence - 置信度
 *
 * @return  none
 */
void Handle_Gesture_Command(uint8_t gesture_id, float confidence)
{
    if(confidence < 0.7f) {
        // 置信度过低，忽略
        return;
    }
    
    switch(gesture_id)
    {
        case GESTURE_FIST:
            // 拳头 - 关闭所有继电器
            GPIO_SetBits(RELAY_PORT, RELAY1_PIN | RELAY2_PIN | RELAY3_PIN);
            relay_state[0] = 0;
            relay_state[1] = 0;
            relay_state[2] = 0;
            printf("All relays OFF - Fist (%.2f)\r\n", confidence);
            break;
            
        case GESTURE_PALM:
            // 手掌 - 开启所有继电器
            GPIO_ResetBits(RELAY_PORT, RELAY1_PIN | RELAY2_PIN | RELAY3_PIN);
            relay_state[0] = 1;
            relay_state[1] = 1;
            relay_state[2] = 1;
            printf("All relays ON - Palm (%.2f)\r\n", confidence);
            break;
            
        case GESTURE_SWIPE_LEFT:
            // 左滑 - 切换继电器1
            if(relay_state[0]) {
                GPIO_SetBits(RELAY_PORT, RELAY1_PIN);
                relay_state[0] = 0;
                printf("Relay 1 OFF - Swipe Left (%.2f)\r\n", confidence);
            } else {
                GPIO_ResetBits(RELAY_PORT, RELAY1_PIN);
                relay_state[0] = 1;
                printf("Relay 1 ON - Swipe Left (%.2f)\r\n", confidence);
            }
            break;
            
        case GESTURE_SWIPE_RIGHT:
            // 右滑 - 切换继电器2
            if(relay_state[1]) {
                GPIO_SetBits(RELAY_PORT, RELAY2_PIN);
                relay_state[1] = 0;
                printf("Relay 2 OFF - Swipe Right (%.2f)\r\n", confidence);
            } else {
                GPIO_ResetBits(RELAY_PORT, RELAY2_PIN);
                relay_state[1] = 1;
                printf("Relay 2 ON - Swipe Right (%.2f)\r\n", confidence);
            }
            break;
            
        case GESTURE_SWIPE_UP:
            // 上滑 - 切换继电器3
            if(relay_state[2]) {
                GPIO_SetBits(RELAY_PORT, RELAY3_PIN);
                relay_state[2] = 0;
                printf("Relay 3 OFF - Swipe Up (%.2f)\r\n", confidence);
            } else {
                GPIO_ResetBits(RELAY_PORT, RELAY3_PIN);
                relay_state[2] = 1;
                printf("Relay 3 ON - Swipe Up (%.2f)\r\n", confidence);
            }
            break;
            
        case GESTURE_SWIPE_DOWN:
            // 下滑 - 关闭所有继电器
            GPIO_SetBits(RELAY_PORT, RELAY1_PIN | RELAY2_PIN | RELAY3_PIN);
            relay_state[0] = 0;
            relay_state[1] = 0;
            relay_state[2] = 0;
            printf("All relays OFF - Swipe Down (%.2f)\r\n", confidence);
            break;
            
        case GESTURE_PINCH:
            // 捏合 - 切换继电器1和2
            if(relay_state[0]) {
                GPIO_SetBits(RELAY_PORT, RELAY1_PIN);
                relay_state[0] = 0;
            } else {
                GPIO_ResetBits(RELAY_PORT, RELAY1_PIN);
                relay_state[0] = 1;
            }
            
            if(relay_state[1]) {
                GPIO_SetBits(RELAY_PORT, RELAY2_PIN);
                relay_state[1] = 0;
            } else {
                GPIO_ResetBits(RELAY_PORT, RELAY2_PIN);
                relay_state[1] = 1;
            }
            printf("Relay 1&2 toggled - Pinch (%.2f)\r\n", confidence);
            break;
            
        case GESTURE_OK:
            // OK手势 - 切换继电器2和3
            if(relay_state[1]) {
                GPIO_SetBits(RELAY_PORT, RELAY2_PIN);
                relay_state[1] = 0;
            } else {
                GPIO_ResetBits(RELAY_PORT, RELAY2_PIN);
                relay_state[1] = 1;
            }
            
            if(relay_state[2]) {
                GPIO_SetBits(RELAY_PORT, RELAY3_PIN);
                relay_state[2] = 0;
            } else {
                GPIO_ResetBits(RELAY_PORT, RELAY3_PIN);
                relay_state[2] = 1;
            }
            printf("Relay 2&3 toggled - OK (%.2f)\r\n", confidence);
            break;
            
        default:
            break;
    }
}
