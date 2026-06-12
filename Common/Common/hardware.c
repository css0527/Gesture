/********************************** (C) COPYRIGHT  *******************************
* File Name          : hardware.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2025/03/01
* Description        : This file provides all the hardware firmware functions.
*********************************************************************************
* Copyright (c) 2025 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#include "hardware.h"
#include "dvp.h"
#include "ch32h417_dvp.h"
#include "ch32h417_swpmi.h"
#include "ch32h417_usbss_device.h"
#include "ch32h417_usbhs_device.h"

void Hardware(void)
{
    RCC_HB2PeriphClockCmd(RCC_HB2Periph_AFIO, ENABLE); 
    RCC_HB1PeriphClockCmd(RCC_HB1Periph_SWPMI, ENABLE);
    SWPMI_BypassCmd(ENABLE);

    /* 初始化 OV2640 摄像头 */
    while(OV2640_Init())
    {
        printf("Camera model Err\r\n");
        Delay_Ms(500);
    }

    /* 初始化 DVP */
    dvp_Init();

    /* 初始化 USB 定时器和 USB 设备 */
    USB_Timer_Init();
    USBSS_Device_Init(ENABLE);
    
    while (1)
    {
        // 主循环：摄像头数据通过UVC传输到PC
        // 同时将图像数据准备给V5F进行手势识别
    }
}
