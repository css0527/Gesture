################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../User/tflm/tensorflow/lite/micro/arena_allocator/non_persistent_arena_buffer_allocator.cc \
../User/tflm/tensorflow/lite/micro/arena_allocator/persistent_arena_buffer_allocator.cc \
../User/tflm/tensorflow/lite/micro/arena_allocator/recording_single_arena_buffer_allocator.cc \
../User/tflm/tensorflow/lite/micro/arena_allocator/single_arena_buffer_allocator.cc 

CC_DEPS += \
./User/tflm/tensorflow/lite/micro/arena_allocator/non_persistent_arena_buffer_allocator.d \
./User/tflm/tensorflow/lite/micro/arena_allocator/persistent_arena_buffer_allocator.d \
./User/tflm/tensorflow/lite/micro/arena_allocator/recording_single_arena_buffer_allocator.d \
./User/tflm/tensorflow/lite/micro/arena_allocator/single_arena_buffer_allocator.d 

OBJS += \
./User/tflm/tensorflow/lite/micro/arena_allocator/non_persistent_arena_buffer_allocator.o \
./User/tflm/tensorflow/lite/micro/arena_allocator/persistent_arena_buffer_allocator.o \
./User/tflm/tensorflow/lite/micro/arena_allocator/recording_single_arena_buffer_allocator.o \
./User/tflm/tensorflow/lite/micro/arena_allocator/single_arena_buffer_allocator.o 

DIR_OBJS += \
./User/tflm/tensorflow/lite/micro/arena_allocator/*.o \

DIR_DEPS += \
./User/tflm/tensorflow/lite/micro/arena_allocator/*.d \

DIR_EXPANDS += \
./User/tflm/tensorflow/lite/micro/arena_allocator/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
User/tflm/tensorflow/lite/micro/arena_allocator/%.o: ../User/tflm/tensorflow/lite/micro/arena_allocator/%.cc
	@	riscv-wch-elf-g++ -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/Common/Common" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/Common/Common/DVP" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/Common/Common/UVC" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/Common/Core" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/Common/Debug" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/Common/Peripheral" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/Common/Startup" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/V3F/Ld" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/V3F/User" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/V3F/User/tflm" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/V3F/User/tflm/third_party" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/V3F/User/tflm/third_party/flatbuffers" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/V3F/User/tflm/third_party/flatbuffers/include" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/V3F/User/tflm/third_party/gemmlowp" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/V3F/User/tflm/third_party/kissfft" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/V3F/User/tflm/third_party/ruy" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

