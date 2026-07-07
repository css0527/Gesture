################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/tflm/third_party/kissfft/kiss_fft.c 

C_DEPS += \
./User/tflm/third_party/kissfft/kiss_fft.d 

OBJS += \
./User/tflm/third_party/kissfft/kiss_fft.o 

DIR_OBJS += \
./User/tflm/third_party/kissfft/*.o \

DIR_DEPS += \
./User/tflm/third_party/kissfft/*.d \

DIR_EXPANDS += \
./User/tflm/third_party/kissfft/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
User/tflm/third_party/kissfft/%.o: ../User/tflm/third_party/kissfft/%.c
	@	riscv-wch-elf-gcc -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DCore_V5F -I"d:/project/CQLM/TFLM/LD/gesture/Common/Debug" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Core" -I"d:/project/CQLM/TFLM/LD/gesture/V5F/User" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Peripheral/inc" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Common" -I"d:/project/CQLM/TFLM/LD/gesture/V5F/User/tflm" -I"d:/project/CQLM/TFLM/LD/gesture/V5F/User/tflm/third_party/flatbuffers/include" -I"d:/project/CQLM/TFLM/LD/gesture/V5F/User/tflm/third_party/gemmlowp" -I"d:/project/CQLM/TFLM/LD/gesture/V5F/User/tflm/third_party/kissfft" -I"d:/project/CQLM/TFLM/LD/gesture/V5F/User/tflm/third_party/ruy" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Common/DVP" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Common/UVC" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

