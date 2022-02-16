################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Archive.cpp \
../src/Cache.cpp \
../src/ImageProcess.cpp \
../src/Window.cpp \
../src/main.cpp 

CPP_DEPS += \
./src/Archive.d \
./src/Cache.d \
./src/ImageProcess.d \
./src/Window.d \
./src/main.d 

OBJS += \
./src/Archive.o \
./src/Cache.o \
./src/ImageProcess.o \
./src/Window.o \
./src/main.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/opencv4 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Archive.d ./src/Archive.o ./src/Cache.d ./src/Cache.o ./src/ImageProcess.d ./src/ImageProcess.o ./src/Window.d ./src/Window.o ./src/main.d ./src/main.o

.PHONY: clean-src

