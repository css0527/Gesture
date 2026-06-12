// /* Copyright 2023 The TensorFlow Authors. All Rights Reserved.

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ==============================================================================*/
// #include "tensorflow/lite/micro/micro_interpreter.h"
// #include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
// #include "tensorflow/lite/micro/system_setup.h"
// #include "tensorflow/lite/micro/micro_log.h"
// #include "tensorflow/lite/schema/schema_generated.h"
// #include "debug.h"

// // ========== 共享内存和图像尺寸定义 ==========
// // 如果 debug.h 中没有定义，则在这里定义
// #ifndef SHARED_IMAGE_ADDR
// #define SHARED_MEM_BASE 0x200C0000
// #define SHARED_IMAGE_ADDR (SHARED_MEM_BASE + 1024)
// #define SHARED_IMAGE_WIDTH 224
// #define SHARED_IMAGE_HEIGHT 224
// #define SHARED_IMAGE_CHANNELS 3
// #define SHARED_IMAGE_SIZE (SHARED_IMAGE_WIDTH * SHARED_IMAGE_HEIGHT * SHARED_IMAGE_CHANNELS)
// #endif

// // 使用定义
// #define IMAGE_WIDTH SHARED_IMAGE_WIDTH
// #define IMAGE_HEIGHT SHARED_IMAGE_HEIGHT
// #define IMAGE_SIZE SHARED_IMAGE_SIZE

// // ========== 手势模型数据 ==========
// // 请确认模型文件的实际路径
// // 如果模型文件在 User/tflm/examples/hello_world/models/ 目录下
// #include "examples/hello_world/models/gesture_model.h"

// // ========== 手势识别配置 ==========
// constexpr int kGestureClassCount = 9; // fist, palm, swipe_left, swipe_right, swipe_up, swipe_down, pinch, ok, none

// const char* gesture_names[] = {
//     "fist", "palm", "swipe_left", "swipe_right", 
//     "swipe_up", "swipe_down", "pinch", "ok", "none"
// };

// // ========== 继电器控制函数 ==========
// void control_relay(int gesture_idx) {
//     switch(gesture_idx) {
//     case 1: // palm
//         MicroPrintf(">>> RELAY ON <<< (Gesture: %s)", gesture_names[gesture_idx]);
//         break;
//     case 0: // fist
//         MicroPrintf(">>> RELAY OFF <<< (Gesture: %s)", gesture_names[gesture_idx]);
//         break;
//     default:
//         MicroPrintf("Gesture: %s (no relay action)", gesture_names[gesture_idx]);
//         break;
//     }
// }

// // ========== 主函数 ==========
// int main(int argc, char* argv[]) {
//     tflite::InitializeTarget();

//     MicroPrintf("========================================");
//     MicroPrintf("Gesture Recognition System Starting...");
//     MicroPrintf("Shared memory address: 0x%08X", (uint32_t)SHARED_IMAGE_ADDR);
//     MicroPrintf("Image size: %d bytes (%dx%dx%d)", IMAGE_SIZE, IMAGE_WIDTH, IMAGE_HEIGHT, SHARED_IMAGE_CHANNELS);
//     MicroPrintf("========================================");

//     // 加载模型
//     const tflite::Model* model = tflite::GetModel(gesture_model_data);
//     if (model->version() != TFLITE_SCHEMA_VERSION) {
//         MicroPrintf("Model version mismatch! Expected: %d, Got: %d", 
//                    TFLITE_SCHEMA_VERSION, model->version());
//         return -1;
//     }
//     MicroPrintf("Model loaded successfully.");

//     // 注册算子
//     static tflite::MicroMutableOpResolver<10> op_resolver;
//     op_resolver.AddConv2D();
//     op_resolver.AddMaxPool2D();
//     op_resolver.AddFullyConnected();
//     op_resolver.AddSoftmax();
//     op_resolver.AddReshape();
//     MicroPrintf("Operators registered.");

//     // 分配 Tensor Arena (102KB)
//     constexpr int kTensorArenaSize = 102 * 1024;
//     static uint8_t tensor_arena[kTensorArenaSize];

//     tflite::MicroInterpreter interpreter(model, op_resolver, tensor_arena, kTensorArenaSize);

//     if (interpreter.AllocateTensors() != kTfLiteOk) {
//         MicroPrintf("Failed to allocate tensors!");
//         return -1;
//     }
//     MicroPrintf("Tensors allocated.");

//     TfLiteTensor* input = interpreter.input(0);
//     TfLiteTensor* output = interpreter.output(0);

//     if (input == nullptr || output == nullptr) {
//         MicroPrintf("Input or output tensor is null!");
//         return -1;
//     }

//     MicroPrintf("Input tensor size: %d bytes", input->bytes);
//     MicroPrintf("Output tensor size: %d bytes", output->bytes);
//     MicroPrintf("========================================");
//     MicroPrintf("Waiting for images from V3F...");
//     MicroPrintf("========================================");

//     uint32_t frame_counter = 0;
//     uint8_t* shared_image = (uint8_t*)SHARED_IMAGE_ADDR;

//     while (1) {
//         // 尝试获取信号量
//         if (HSEM_Take(HSEM_GESTURE_SYNC, 0)) {
//             // 复制图像数据
//             memcpy(input->data.uint8, shared_image, IMAGE_SIZE);

//             // 执行推理
//             TfLiteStatus invoke_status = interpreter.Invoke();

//             if (invoke_status == kTfLiteOk) {
//                 // 获取结果
//                 int max_index = 0;
//                 float max_value = output->data.f[0];
//                 for (int i = 1; i < kGestureClassCount; i++) {
//                     if (output->data.f[i] > max_value) {
//                         max_value = output->data.f[i];
//                         max_index = i;
//                     }
//                 }

//                 // 只显示置信度高的结果
//                 if (max_value > 0.5f) {
//                     MicroPrintf("[Frame %d] Gesture: %s (%.1f%%)", 
//                                ++frame_counter, gesture_names[max_index], max_value * 100.0f);
//                     control_relay(max_index);
//                 }
//             } else {
//                 MicroPrintf("Invoke failed!");
//             }

//             // 释放信号量
//             HSEM_ReleaseOneSem(HSEM_GESTURE_SYNC, 0);
//         }

//         // 简单延时，避免过高的CPU占用
//         for (volatile int i = 0; i < 10000; i++);
//     }

//     return 0;
// }


