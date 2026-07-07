################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
d:/project/CQLM/TFLM/LD/gesture/Common/Common/DVP/dvp.c \
d:/project/CQLM/TFLM/LD/gesture/Common/Common/DVP/ov2640.c 

C_DEPS += \
./Common/DVP/dvp.d \
./Common/DVP/ov2640.d 

OBJS += \
./Common/DVP/dvp.o \
./Common/DVP/ov2640.o 

DIR_OBJS += \
./Common/DVP/*.o \

DIR_DEPS += \
./Common/DVP/*.d \

DIR_EXPANDS += \
./Common/DVP/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
Common/DVP/dvp.o: d:/project/CQLM/TFLM/LD/gesture/Common/Common/DVP/dvp.c
	@	riscv-wch-elf-gcc -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DCore_V3F -I"d:/project/CQLM/TFLM/LD/gesture/Common/Debug" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Core" -I"d:/project/CQLM/TFLM/LD/gesture/V3F/User" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Peripheral/inc" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Common" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Common/DVP" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Common/UVC" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Common/DVP/ov2640.o: d:/project/CQLM/TFLM/LD/gesture/Common/Common/DVP/ov2640.c
	@	riscv-wch-elf-gcc -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DCore_V3F -I"d:/project/CQLM/TFLM/LD/gesture/Common/Debug" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Core" -I"d:/project/CQLM/TFLM/LD/gesture/V3F/User" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Peripheral/inc" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Common" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Common/DVP" -I"d:/project/CQLM/TFLM/LD/gesture/Common/Common/UVC" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

