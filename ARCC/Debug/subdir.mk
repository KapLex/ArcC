################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Collision.c \
../Draw.c \
../Font.c \
../Input.c \
../Keyboard.c \
../Log.c \
../Math.c \
../Mouse.c \
../Point.c \
../Rect.c \
../Size.c \
../Sound.c \
../Texture.c \
../Time.c \
../Util.c \
../Window.c 

OBJS += \
./Collision.o \
./Draw.o \
./Font.o \
./Input.o \
./Keyboard.o \
./Log.o \
./Math.o \
./Mouse.o \
./Point.o \
./Rect.o \
./Size.o \
./Sound.o \
./Texture.o \
./Time.o \
./Util.o \
./Window.o 

C_DEPS += \
./Collision.d \
./Draw.d \
./Font.d \
./Input.d \
./Keyboard.d \
./Log.d \
./Math.d \
./Mouse.d \
./Point.d \
./Rect.d \
./Size.d \
./Sound.d \
./Texture.d \
./Time.d \
./Util.d \
./Window.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include -I/usr/include/freetype2 -O0 -g3 -Wall -c -fmessage-length=0 -std=gnu99 -Wstrict-prototypes -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


