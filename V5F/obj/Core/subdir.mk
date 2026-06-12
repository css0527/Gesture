################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
d:/project/CQLM/MEU/V3Fenable1/Common/Core/core_riscv.c 

C_DEPS += \
./Core/core_riscv.d 

OBJS += \
./Core/core_riscv.o 

DIR_OBJS += \
./Core/*.o \

DIR_DEPS += \
./Core/*.d \

DIR_EXPANDS += \
./Core/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
Core/core_riscv.o: d:/project/CQLM/MEU/V3Fenable1/Common/Core/core_riscv.c
	@	riscv-wch-elf-gcc -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DCore_V5F -I"d:/project/CQLM/MEU/V3Fenable1/Common/Debug" -I"d:/project/CQLM/MEU/V3Fenable1/Common/Core" -I"d:/project/CQLM/MEU/V3Fenable1/V5F/User" -I"d:/project/CQLM/MEU/V3Fenable1/Common/Peripheral/inc" -I"d:/project/CQLM/MEU/V3Fenable1/Common/Common" -I"d:/project/CQLM/MEU/V3Fenable1/V5F/User/tflm" -I"d:/project/CQLM/MEU/V3Fenable1/V5F/User/tflm/third_party/flatbuffers/include" -I"d:/project/CQLM/MEU/V3Fenable1/V5F/User/tflm/third_party/gemmlowp" -I"d:/project/CQLM/MEU/V3Fenable1/V5F/User/tflm/third_party/kissfft" -I"d:/project/CQLM/MEU/V3Fenable1/V5F/User/tflm/third_party/ruy" -I"d:/project/CQLM/MEU/V3Fenable1/Common/Common/DVP" -I"d:/project/CQLM/MEU/V3Fenable1/Common/Common/UVC" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

