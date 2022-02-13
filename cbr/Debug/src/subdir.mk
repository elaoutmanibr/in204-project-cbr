################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/archivereader.cpp \
../src/display.cpp \
../src/imageProcess.cpp \
../src/imgprocess.cpp \
../src/main.cpp \
../src/window.cpp 

CPP_DEPS += \
./src/archivereader.d \
./src/display.d \
./src/imageProcess.d \
./src/imgprocess.d \
./src/main.d \
./src/window.d 

OBJS += \
./src/archivereader.o \
./src/display.o \
./src/imageProcess.o \
./src/imgprocess.o \
./src/main.o \
./src/window.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/opencv4 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/archivereader.d ./src/archivereader.o ./src/display.d ./src/display.o ./src/imageProcess.d ./src/imageProcess.o ./src/imgprocess.d ./src/imgprocess.o ./src/main.d ./src/main.o ./src/window.d ./src/window.o

.PHONY: clean-src

