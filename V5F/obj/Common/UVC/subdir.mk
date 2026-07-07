################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
d:/project/CQLM/TFLM/LD/gesture/Common/Common/UVC/uvc.c \
d:/project/CQLM/TFLM/LD/gesture/Common/Common/UVC/uvcclassdes.c 

C_DEPS += \
./Common/UVC/uvc.d \
./Common/UVC/uvcclassdes.d 

OBJS += \
./Common/UVC/uvc.o \
./Common/UVC/uvcclassdes.o 

DIR_OBJS += \
./Common/UVC/*.o \

DIR_DEPS += \
./Common/UVC/*.d \

DIR_EXPANDS += \
./Common/UVC/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
Common/UVC/uvc.o: d:/project/CQLM/TFLM/LD/gesture/Common/Common/UVC/uvc.c
	@	riscv-wch-elf-gcc -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DCore_V5F -I"d:/project/CQLM/TFLM/LD/gesture/Common/Debug" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Core" -I"d:/project/CQLM/TFLM/LD/gesture/V5F/User" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Peripheral/inc" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Common" -I"d:/project/CQLM/TFLM/LD/gesture/V5F/User/tflm" -I"d:/project/CQLM/TFLM/LD/gesture/V5F/User/tflm/third_party/flatbuffers/include" -I"d:/project/CQLM/TFLM/LD/gesture/V5F/User/tflm/third_party/gemmlowp" -I"d:/project/CQLM/TFLM/LD/gesture/V5F/User/tflm/third_party/kissfft" -I"d:/project/CQLM/TFLM/LD/gesture/V5F/User/tflm/third_party/ruy" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Common/DVP" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Common/UVC" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Common/UVC/uvcclassdes.o: d:/project/CQLM/TFLM/LD/gesture/Common/Common/UVC/uvcclassdes.c
	@	riscv-wch-elf-gcc -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DCore_V5F -I"d:/project/CQLM/TFLM/LD/gesture/Common/Debug" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Core" -I"d:/project/CQLM/TFLM/LD/gesture/V5F/User" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Peripheral/inc" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Common" -I"d:/project/CQLM/TFLM/LD/gesture/V5F/User/tflm" -I"d:/project/CQLM/TFLM/LD/gesture/V5F/User/tflm/third_party/flatbuffers/include" -I"d:/project/CQLM/TFLM/LD/gesture/V5F/User/tflm/third_party/gemmlowp" -I"d:/project/CQLM/TFLM/LD/gesture/V5F/User/tflm/third_party/kissfft" -I"d:/project/CQLM/TFLM/LD/gesture/V5F/User/tflm/third_party/ruy" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Common/DVP" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Common/UVC" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

