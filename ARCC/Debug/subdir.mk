################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Font.c \
../Log.c \
../Time.c \
../Window.c 

OBJS += \
./Font.o \
./Log.o \
./Time.o \
./Window.o 

C_DEPS += \
./Font.d \
./Log.d \
./Time.d \
./Window.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include -I/usr/include/freetype2 -O0 -g3 -Wall -c -fmessage-length=0 -std=gnu99 -Wstrict-prototypes -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


