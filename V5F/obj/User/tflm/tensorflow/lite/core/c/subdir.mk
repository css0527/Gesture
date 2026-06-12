################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../User/tflm/tensorflow/lite/core/c/common.cc 

CC_DEPS += \
./User/tflm/tensorflow/lite/core/c/common.d 

OBJS += \
./User/tflm/tensorflow/lite/core/c/common.o 

DIR_OBJS += \
./User/tflm/tensorflow/lite/core/c/*.o \

DIR_DEPS += \
./User/tflm/tensorflow/lite/core/c/*.d \

DIR_EXPANDS += \
./User/tflm/tensorflow/lite/core/c/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
User/tflm/tensorflow/lite/core/c/%.o: ../User/tflm/tensorflow/lite/core/c/%.cc
	@	riscv-wch-elf-g++ -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DTF_LITE_USE_GLOBAL_CMATH_FUNCTIONS -DTF_LITE_STATIC_MEMORY -DTF_LITE_USE_GLOBAL_MIN -DTF_LITE_USE_GLOBAL_MAX -I"d:/project/CQLM/MEU/V3Fenable1/Common/Common" -I"d:/project/CQLM/MEU/V3Fenable1/Common/Core" -I"d:/project/CQLM/MEU/V3Fenable1/Common/Debug" -I"d:/project/CQLM/MEU/V3Fenable1/Common/Peripheral/inc" -I"d:/project/CQLM/MEU/V3Fenable1/V5F/User" -I"d:/project/CQLM/MEU/V3Fenable1/V5F/User/tflm" -I"d:/project/CQLM/MEU/V3Fenable1/V5F/User/tflm/third_party/flatbuffers/include" -I"d:/project/CQLM/MEU/V3Fenable1/V5F/User/tflm/third_party/gemmlowp" -I"d:/project/CQLM/MEU/V3Fenable1/V5F/User/tflm/third_party/kissfft" -I"d:/project/CQLM/MEU/V3Fenable1/V5F/User/tflm/third_party/ruy" -I"d:/project/CQLM/MEU/V3Fenable1/Common/Common/DVP" -I"d:/project/CQLM/MEU/V3Fenable1/Common/Common/UVC" -std=gnu++17 -fabi-version=0 -fno-exceptions -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

