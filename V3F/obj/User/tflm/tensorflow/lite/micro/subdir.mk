################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../User/tflm/tensorflow/lite/micro/debug_log.cc \
../User/tflm/tensorflow/lite/micro/fake_micro_context.cc \
../User/tflm/tensorflow/lite/micro/flatbuffer_utils.cc \
../User/tflm/tensorflow/lite/micro/hexdump.cc \
../User/tflm/tensorflow/lite/micro/memory_helpers.cc \
../User/tflm/tensorflow/lite/micro/micro_allocation_info.cc \
../User/tflm/tensorflow/lite/micro/micro_allocator.cc \
../User/tflm/tensorflow/lite/micro/micro_context.cc \
../User/tflm/tensorflow/lite/micro/micro_interpreter.cc \
../User/tflm/tensorflow/lite/micro/micro_interpreter_context.cc \
../User/tflm/tensorflow/lite/micro/micro_interpreter_graph.cc \
../User/tflm/tensorflow/lite/micro/micro_log.cc \
../User/tflm/tensorflow/lite/micro/micro_op_resolver.cc \
../User/tflm/tensorflow/lite/micro/micro_profiler.cc \
../User/tflm/tensorflow/lite/micro/micro_resource_variable.cc \
../User/tflm/tensorflow/lite/micro/micro_time.cc \
../User/tflm/tensorflow/lite/micro/micro_utils.cc \
../User/tflm/tensorflow/lite/micro/mock_micro_graph.cc \
../User/tflm/tensorflow/lite/micro/recording_micro_allocator.cc \
../User/tflm/tensorflow/lite/micro/test_helper_custom_ops.cc \
../User/tflm/tensorflow/lite/micro/test_helpers.cc 

CC_DEPS += \
./User/tflm/tensorflow/lite/micro/debug_log.d \
./User/tflm/tensorflow/lite/micro/fake_micro_context.d \
./User/tflm/tensorflow/lite/micro/flatbuffer_utils.d \
./User/tflm/tensorflow/lite/micro/hexdump.d \
./User/tflm/tensorflow/lite/micro/memory_helpers.d \
./User/tflm/tensorflow/lite/micro/micro_allocation_info.d \
./User/tflm/tensorflow/lite/micro/micro_allocator.d \
./User/tflm/tensorflow/lite/micro/micro_context.d \
./User/tflm/tensorflow/lite/micro/micro_interpreter.d \
./User/tflm/tensorflow/lite/micro/micro_interpreter_context.d \
./User/tflm/tensorflow/lite/micro/micro_interpreter_graph.d \
./User/tflm/tensorflow/lite/micro/micro_log.d \
./User/tflm/tensorflow/lite/micro/micro_op_resolver.d \
./User/tflm/tensorflow/lite/micro/micro_profiler.d \
./User/tflm/tensorflow/lite/micro/micro_resource_variable.d \
./User/tflm/tensorflow/lite/micro/micro_time.d \
./User/tflm/tensorflow/lite/micro/micro_utils.d \
./User/tflm/tensorflow/lite/micro/mock_micro_graph.d \
./User/tflm/tensorflow/lite/micro/recording_micro_allocator.d \
./User/tflm/tensorflow/lite/micro/test_helper_custom_ops.d \
./User/tflm/tensorflow/lite/micro/test_helpers.d 

OBJS += \
./User/tflm/tensorflow/lite/micro/debug_log.o \
./User/tflm/tensorflow/lite/micro/fake_micro_context.o \
./User/tflm/tensorflow/lite/micro/flatbuffer_utils.o \
./User/tflm/tensorflow/lite/micro/hexdump.o \
./User/tflm/tensorflow/lite/micro/memory_helpers.o \
./User/tflm/tensorflow/lite/micro/micro_allocation_info.o \
./User/tflm/tensorflow/lite/micro/micro_allocator.o \
./User/tflm/tensorflow/lite/micro/micro_context.o \
./User/tflm/tensorflow/lite/micro/micro_interpreter.o \
./User/tflm/tensorflow/lite/micro/micro_interpreter_context.o \
./User/tflm/tensorflow/lite/micro/micro_interpreter_graph.o \
./User/tflm/tensorflow/lite/micro/micro_log.o \
./User/tflm/tensorflow/lite/micro/micro_op_resolver.o \
./User/tflm/tensorflow/lite/micro/micro_profiler.o \
./User/tflm/tensorflow/lite/micro/micro_resource_variable.o \
./User/tflm/tensorflow/lite/micro/micro_time.o \
./User/tflm/tensorflow/lite/micro/micro_utils.o \
./User/tflm/tensorflow/lite/micro/mock_micro_graph.o \
./User/tflm/tensorflow/lite/micro/recording_micro_allocator.o \
./User/tflm/tensorflow/lite/micro/test_helper_custom_ops.o \
./User/tflm/tensorflow/lite/micro/test_helpers.o 

DIR_OBJS += \
./User/tflm/tensorflow/lite/micro/*.o \

DIR_DEPS += \
./User/tflm/tensorflow/lite/micro/*.d \

DIR_EXPANDS += \
./User/tflm/tensorflow/lite/micro/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
User/tflm/tensorflow/lite/micro/%.o: ../User/tflm/tensorflow/lite/micro/%.cc
	@	riscv-wch-elf-g++ -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/Common/Common" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/Common/Common/DVP" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/Common/Common/UVC" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/Common/Core" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/Common/Debug" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/Common/Peripheral" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/Common/Startup" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/V3F/Ld" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/V3F/User" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/V3F/User/tflm" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/V3F/User/tflm/third_party" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/V3F/User/tflm/third_party/flatbuffers" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/V3F/User/tflm/third_party/flatbuffers/include" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/V3F/User/tflm/third_party/gemmlowp" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/V3F/User/tflm/third_party/kissfft" -I"d:/project/CQLM/MEU/TFLM+UVC+DVP - 副本/V3F/User/tflm/third_party/ruy" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

