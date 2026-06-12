################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../User/tflm/signal/micro/kernels/delay.cc \
../User/tflm/signal/micro/kernels/energy.cc \
../User/tflm/signal/micro/kernels/fft_auto_scale_common.cc \
../User/tflm/signal/micro/kernels/fft_auto_scale_kernel.cc \
../User/tflm/signal/micro/kernels/filter_bank.cc \
../User/tflm/signal/micro/kernels/filter_bank_log.cc \
../User/tflm/signal/micro/kernels/filter_bank_spectral_subtraction.cc \
../User/tflm/signal/micro/kernels/filter_bank_square_root.cc \
../User/tflm/signal/micro/kernels/filter_bank_square_root_common.cc \
../User/tflm/signal/micro/kernels/framer.cc \
../User/tflm/signal/micro/kernels/irfft.cc \
../User/tflm/signal/micro/kernels/overlap_add.cc \
../User/tflm/signal/micro/kernels/pcan.cc \
../User/tflm/signal/micro/kernels/rfft.cc \
../User/tflm/signal/micro/kernels/stacker.cc \
../User/tflm/signal/micro/kernels/window.cc 

CC_DEPS += \
./User/tflm/signal/micro/kernels/delay.d \
./User/tflm/signal/micro/kernels/energy.d \
./User/tflm/signal/micro/kernels/fft_auto_scale_common.d \
./User/tflm/signal/micro/kernels/fft_auto_scale_kernel.d \
./User/tflm/signal/micro/kernels/filter_bank.d \
./User/tflm/signal/micro/kernels/filter_bank_log.d \
./User/tflm/signal/micro/kernels/filter_bank_spectral_subtraction.d \
./User/tflm/signal/micro/kernels/filter_bank_square_root.d \
./User/tflm/signal/micro/kernels/filter_bank_square_root_common.d \
./User/tflm/signal/micro/kernels/framer.d \
./User/tflm/signal/micro/kernels/irfft.d \
./User/tflm/signal/micro/kernels/overlap_add.d \
./User/tflm/signal/micro/kernels/pcan.d \
./User/tflm/signal/micro/kernels/rfft.d \
./User/tflm/signal/micro/kernels/stacker.d \
./User/tflm/signal/micro/kernels/window.d 

OBJS += \
./User/tflm/signal/micro/kernels/delay.o \
./User/tflm/signal/micro/kernels/energy.o \
./User/tflm/signal/micro/kernels/fft_auto_scale_common.o \
./User/tflm/signal/micro/kernels/fft_auto_scale_kernel.o \
./User/tflm/signal/micro/kernels/filter_bank.o \
./User/tflm/signal/micro/kernels/filter_bank_log.o \
./User/tflm/signal/micro/kernels/filter_bank_spectral_subtraction.o \
./User/tflm/signal/micro/kernels/filter_bank_square_root.o \
./User/tflm/signal/micro/kernels/filter_bank_square_root_common.o \
./User/tflm/signal/micro/kernels/framer.o \
./User/tflm/signal/micro/kernels/irfft.o \
./User/tflm/signal/micro/kernels/overlap_add.o \
./User/tflm/signal/micro/kernels/pcan.o \
./User/tflm/signal/micro/kernels/rfft.o \
./User/tflm/signal/micro/kernels/stacker.o \
./User/tflm/signal/micro/kernels/window.o 

DIR_OBJS += \
./User/tflm/signal/micro/kernels/*.o \

DIR_DEPS += \
./User/tflm/signal/micro/kernels/*.d \

DIR_EXPANDS += \
./User/tflm/signal/micro/kernels/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
User/tflm/signal/micro/kernels/%.o: ../User/tflm/signal/micro/kernels/%.cc
	@	riscv-wch-elf-g++ -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DTF_LITE_USE_GLOBAL_CMATH_FUNCTIONS -DTF_LITE_STATIC_MEMORY -DTF_LITE_USE_GLOBAL_MIN -DTF_LITE_USE_GLOBAL_MAX -I"d:/project/CQLM/MEU/V3Fenable1/Common/Common" -I"d:/project/CQLM/MEU/V3Fenable1/Common/Core" -I"d:/project/CQLM/MEU/V3Fenable1/Common/Debug" -I"d:/project/CQLM/MEU/V3Fenable1/Common/Peripheral/inc" -I"d:/project/CQLM/MEU/V3Fenable1/V5F/User" -I"d:/project/CQLM/MEU/V3Fenable1/V5F/User/tflm" -I"d:/project/CQLM/MEU/V3Fenable1/V5F/User/tflm/third_party/flatbuffers/include" -I"d:/project/CQLM/MEU/V3Fenable1/V5F/User/tflm/third_party/gemmlowp" -I"d:/project/CQLM/MEU/V3Fenable1/V5F/User/tflm/third_party/kissfft" -I"d:/project/CQLM/MEU/V3Fenable1/V5F/User/tflm/third_party/ruy" -I"d:/project/CQLM/MEU/V3Fenable1/Common/Common/DVP" -I"d:/project/CQLM/MEU/V3Fenable1/Common/Common/UVC" -std=gnu++17 -fabi-version=0 -fno-exceptions -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

