/********************************** (C) COPYRIGHT *******************************
 * File Name          : gesture_handler.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2025/03/01
 * Description        : Gesture processing and relay control handler header.
 *********************************************************************************
 * Copyright (c) 2025 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#ifndef __GESTURE_HANDLER_H
#define __GESTURE_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ch32h417.h"

// º¯ÊýÉùÃ÷
void Gesture_Relay_Init(void);
void Handle_Gesture_Command(uint8_t gesture_id, float confidence);

#ifdef __cplusplus
}
#endif

#endif /* __GESTURE_HANDLER_H */
