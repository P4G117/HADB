################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Block.cpp \
../src/Disk.cpp \
../src/RAIDClient.cpp \
../src/main.cpp \
../src/tinyxml2.cpp 

OBJS += \
./src/Block.o \
./src/Disk.o \
./src/RAIDClient.o \
./src/main.o \
./src/tinyxml2.o 

CPP_DEPS += \
./src/Block.d \
./src/Disk.d \
./src/RAIDClient.d \
./src/main.d \
./src/tinyxml2.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


