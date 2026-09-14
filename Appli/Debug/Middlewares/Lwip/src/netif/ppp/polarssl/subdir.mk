################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/ppp/polarssl/arc4.c \
C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/ppp/polarssl/des.c \
C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/ppp/polarssl/md4.c \
C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/ppp/polarssl/md5.c \
C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/ppp/polarssl/sha1.c 

OBJS += \
./Middlewares/Lwip/src/netif/ppp/polarssl/arc4.o \
./Middlewares/Lwip/src/netif/ppp/polarssl/des.o \
./Middlewares/Lwip/src/netif/ppp/polarssl/md4.o \
./Middlewares/Lwip/src/netif/ppp/polarssl/md5.o \
./Middlewares/Lwip/src/netif/ppp/polarssl/sha1.o 

C_DEPS += \
./Middlewares/Lwip/src/netif/ppp/polarssl/arc4.d \
./Middlewares/Lwip/src/netif/ppp/polarssl/des.d \
./Middlewares/Lwip/src/netif/ppp/polarssl/md4.d \
./Middlewares/Lwip/src/netif/ppp/polarssl/md5.d \
./Middlewares/Lwip/src/netif/ppp/polarssl/sha1.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Lwip/src/netif/ppp/polarssl/arc4.o: C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/ppp/polarssl/arc4.c Middlewares/Lwip/src/netif/ppp/polarssl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N657xx -D_STM32CUBE_DISCOVERY_N657_ -c -I../Core/Inc -I../../Secure_nsclib -I../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Include -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/config" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/include" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/mtkernel/kernel/knlinc" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Lwip/src/netif/ppp/polarssl/des.o: C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/ppp/polarssl/des.c Middlewares/Lwip/src/netif/ppp/polarssl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N657xx -D_STM32CUBE_DISCOVERY_N657_ -c -I../Core/Inc -I../../Secure_nsclib -I../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Include -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/config" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/include" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/mtkernel/kernel/knlinc" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Lwip/src/netif/ppp/polarssl/md4.o: C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/ppp/polarssl/md4.c Middlewares/Lwip/src/netif/ppp/polarssl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N657xx -D_STM32CUBE_DISCOVERY_N657_ -c -I../Core/Inc -I../../Secure_nsclib -I../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Include -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/config" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/include" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/mtkernel/kernel/knlinc" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Lwip/src/netif/ppp/polarssl/md5.o: C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/ppp/polarssl/md5.c Middlewares/Lwip/src/netif/ppp/polarssl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N657xx -D_STM32CUBE_DISCOVERY_N657_ -c -I../Core/Inc -I../../Secure_nsclib -I../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Include -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/config" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/include" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/mtkernel/kernel/knlinc" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Lwip/src/netif/ppp/polarssl/sha1.o: C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/netif/ppp/polarssl/sha1.c Middlewares/Lwip/src/netif/ppp/polarssl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N657xx -D_STM32CUBE_DISCOVERY_N657_ -c -I../Core/Inc -I../../Secure_nsclib -I../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Include -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/config" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/include" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Appli/mtk3_bsp2/mtkernel/kernel/knlinc" -I"C:/Users/aayus/Documents/tron_26/master/mtk3bsp2_stm32n657/Middlewares/Lwip/src/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Lwip-2f-src-2f-netif-2f-ppp-2f-polarssl

clean-Middlewares-2f-Lwip-2f-src-2f-netif-2f-ppp-2f-polarssl:
	-$(RM) ./Middlewares/Lwip/src/netif/ppp/polarssl/arc4.cyclo ./Middlewares/Lwip/src/netif/ppp/polarssl/arc4.d ./Middlewares/Lwip/src/netif/ppp/polarssl/arc4.o ./Middlewares/Lwip/src/netif/ppp/polarssl/arc4.su ./Middlewares/Lwip/src/netif/ppp/polarssl/des.cyclo ./Middlewares/Lwip/src/netif/ppp/polarssl/des.d ./Middlewares/Lwip/src/netif/ppp/polarssl/des.o ./Middlewares/Lwip/src/netif/ppp/polarssl/des.su ./Middlewares/Lwip/src/netif/ppp/polarssl/md4.cyclo ./Middlewares/Lwip/src/netif/ppp/polarssl/md4.d ./Middlewares/Lwip/src/netif/ppp/polarssl/md4.o ./Middlewares/Lwip/src/netif/ppp/polarssl/md4.su ./Middlewares/Lwip/src/netif/ppp/polarssl/md5.cyclo ./Middlewares/Lwip/src/netif/ppp/polarssl/md5.d ./Middlewares/Lwip/src/netif/ppp/polarssl/md5.o ./Middlewares/Lwip/src/netif/ppp/polarssl/md5.su ./Middlewares/Lwip/src/netif/ppp/polarssl/sha1.cyclo ./Middlewares/Lwip/src/netif/ppp/polarssl/sha1.d ./Middlewares/Lwip/src/netif/ppp/polarssl/sha1.o ./Middlewares/Lwip/src/netif/ppp/polarssl/sha1.su

.PHONY: clean-Middlewares-2f-Lwip-2f-src-2f-netif-2f-ppp-2f-polarssl

