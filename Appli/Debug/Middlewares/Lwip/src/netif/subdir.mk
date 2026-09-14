################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/bridgeif.c \
C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/bridgeif_fdb.c \
C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/ethernet.c \
C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/lowpan6.c \
C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/lowpan6_ble.c \
C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/lowpan6_common.c \
C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/zepif.c 

OBJS += \
./Middlewares/Lwip/src/netif/bridgeif.o \
./Middlewares/Lwip/src/netif/bridgeif_fdb.o \
./Middlewares/Lwip/src/netif/ethernet.o \
./Middlewares/Lwip/src/netif/lowpan6.o \
./Middlewares/Lwip/src/netif/lowpan6_ble.o \
./Middlewares/Lwip/src/netif/lowpan6_common.o \
./Middlewares/Lwip/src/netif/zepif.o 

C_DEPS += \
./Middlewares/Lwip/src/netif/bridgeif.d \
./Middlewares/Lwip/src/netif/bridgeif_fdb.d \
./Middlewares/Lwip/src/netif/ethernet.d \
./Middlewares/Lwip/src/netif/lowpan6.d \
./Middlewares/Lwip/src/netif/lowpan6_ble.d \
./Middlewares/Lwip/src/netif/lowpan6_common.d \
./Middlewares/Lwip/src/netif/zepif.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Lwip/src/netif/bridgeif.o: C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/bridgeif.c Middlewares/Lwip/src/netif/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N657xx -D_STM32CUBE_DISCOVERY_N657_ -c -I../Core/Inc -I../../Secure_nsclib -I../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Include -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/config" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/include" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/mtkernel/kernel/knlinc" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Lwip/src/netif/bridgeif_fdb.o: C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/bridgeif_fdb.c Middlewares/Lwip/src/netif/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N657xx -D_STM32CUBE_DISCOVERY_N657_ -c -I../Core/Inc -I../../Secure_nsclib -I../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Include -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/config" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/include" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/mtkernel/kernel/knlinc" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Lwip/src/netif/ethernet.o: C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/ethernet.c Middlewares/Lwip/src/netif/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N657xx -D_STM32CUBE_DISCOVERY_N657_ -c -I../Core/Inc -I../../Secure_nsclib -I../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Include -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/config" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/include" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/mtkernel/kernel/knlinc" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Lwip/src/netif/lowpan6.o: C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/lowpan6.c Middlewares/Lwip/src/netif/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N657xx -D_STM32CUBE_DISCOVERY_N657_ -c -I../Core/Inc -I../../Secure_nsclib -I../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Include -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/config" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/include" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/mtkernel/kernel/knlinc" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Lwip/src/netif/lowpan6_ble.o: C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/lowpan6_ble.c Middlewares/Lwip/src/netif/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N657xx -D_STM32CUBE_DISCOVERY_N657_ -c -I../Core/Inc -I../../Secure_nsclib -I../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Include -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/config" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/include" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/mtkernel/kernel/knlinc" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Lwip/src/netif/lowpan6_common.o: C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/lowpan6_common.c Middlewares/Lwip/src/netif/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N657xx -D_STM32CUBE_DISCOVERY_N657_ -c -I../Core/Inc -I../../Secure_nsclib -I../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Include -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/config" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/include" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/mtkernel/kernel/knlinc" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Lwip/src/netif/zepif.o: C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/zepif.c Middlewares/Lwip/src/netif/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N657xx -D_STM32CUBE_DISCOVERY_N657_ -c -I../Core/Inc -I../../Secure_nsclib -I../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Include -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/config" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/include" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/mtkernel/kernel/knlinc" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Lwip-2f-src-2f-netif

clean-Middlewares-2f-Lwip-2f-src-2f-netif:
	-$(RM) ./Middlewares/Lwip/src/netif/bridgeif.cyclo ./Middlewares/Lwip/src/netif/bridgeif.d ./Middlewares/Lwip/src/netif/bridgeif.o ./Middlewares/Lwip/src/netif/bridgeif.su ./Middlewares/Lwip/src/netif/bridgeif_fdb.cyclo ./Middlewares/Lwip/src/netif/bridgeif_fdb.d ./Middlewares/Lwip/src/netif/bridgeif_fdb.o ./Middlewares/Lwip/src/netif/bridgeif_fdb.su ./Middlewares/Lwip/src/netif/ethernet.cyclo ./Middlewares/Lwip/src/netif/ethernet.d ./Middlewares/Lwip/src/netif/ethernet.o ./Middlewares/Lwip/src/netif/ethernet.su ./Middlewares/Lwip/src/netif/lowpan6.cyclo ./Middlewares/Lwip/src/netif/lowpan6.d ./Middlewares/Lwip/src/netif/lowpan6.o ./Middlewares/Lwip/src/netif/lowpan6.su ./Middlewares/Lwip/src/netif/lowpan6_ble.cyclo ./Middlewares/Lwip/src/netif/lowpan6_ble.d ./Middlewares/Lwip/src/netif/lowpan6_ble.o ./Middlewares/Lwip/src/netif/lowpan6_ble.su ./Middlewares/Lwip/src/netif/lowpan6_common.cyclo ./Middlewares/Lwip/src/netif/lowpan6_common.d ./Middlewares/Lwip/src/netif/lowpan6_common.o ./Middlewares/Lwip/src/netif/lowpan6_common.su ./Middlewares/Lwip/src/netif/zepif.cyclo ./Middlewares/Lwip/src/netif/zepif.d ./Middlewares/Lwip/src/netif/zepif.o ./Middlewares/Lwip/src/netif/zepif.su

.PHONY: clean-Middlewares-2f-Lwip-2f-src-2f-netif

