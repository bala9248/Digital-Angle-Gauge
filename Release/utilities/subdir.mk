################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_debug_console.c 

OBJS += \
./utilities/fsl_debug_console.o 

C_DEPS += \
./utilities/fsl_debug_console.d 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -I"C:\Users\balap\Desktop\PES\MCU-artifacts\Digital_Angle_Gauge\board" -I"C:\Users\balap\Desktop\PES\MCU-artifacts\Digital_Angle_Gauge\source" -I"C:\Users\balap\Desktop\PES\MCU-artifacts\Digital_Angle_Gauge" -I"C:\Users\balap\Desktop\PES\MCU-artifacts\Digital_Angle_Gauge\drivers" -I"C:\Users\balap\Desktop\PES\MCU-artifacts\Digital_Angle_Gauge\CMSIS" -I"C:\Users\balap\Desktop\PES\MCU-artifacts\Digital_Angle_Gauge\utilities" -I"C:\Users\balap\Desktop\PES\MCU-artifacts\Digital_Angle_Gauge\startup" -Os -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


