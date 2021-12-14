################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Command_handler.c \
../source/I2C.c \
../source/LED.c \
../source/accelerometer.c \
../source/cbfifo.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/switch.c \
../source/sysclock.c \
../source/test_DAG.c \
../source/test_LED.c \
../source/test_accelerometer.c \
../source/test_cbfifo.c \
../source/test_interrupts.c \
../source/timer.c \
../source/touch_sensor.c \
../source/uart.c \
../source/user_io.c 

OBJS += \
./source/Command_handler.o \
./source/I2C.o \
./source/LED.o \
./source/accelerometer.o \
./source/cbfifo.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/switch.o \
./source/sysclock.o \
./source/test_DAG.o \
./source/test_LED.o \
./source/test_accelerometer.o \
./source/test_cbfifo.o \
./source/test_interrupts.o \
./source/timer.o \
./source/touch_sensor.o \
./source/uart.o \
./source/user_io.o 

C_DEPS += \
./source/Command_handler.d \
./source/I2C.d \
./source/LED.d \
./source/accelerometer.d \
./source/cbfifo.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/switch.d \
./source/sysclock.d \
./source/test_DAG.d \
./source/test_LED.d \
./source/test_accelerometer.d \
./source/test_cbfifo.d \
./source/test_interrupts.d \
./source/timer.d \
./source/touch_sensor.d \
./source/uart.d \
./source/user_io.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\balap\Desktop\PES\MCU-artifacts\Digital_Angle_Gauge\board" -I"C:\Users\balap\Desktop\PES\MCU-artifacts\Digital_Angle_Gauge\source" -I"C:\Users\balap\Desktop\PES\MCU-artifacts\Digital_Angle_Gauge" -I"C:\Users\balap\Desktop\PES\MCU-artifacts\Digital_Angle_Gauge\drivers" -I"C:\Users\balap\Desktop\PES\MCU-artifacts\Digital_Angle_Gauge\CMSIS" -I"C:\Users\balap\Desktop\PES\MCU-artifacts\Digital_Angle_Gauge\utilities" -I"C:\Users\balap\Desktop\PES\MCU-artifacts\Digital_Angle_Gauge\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


