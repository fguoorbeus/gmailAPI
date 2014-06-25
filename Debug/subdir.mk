################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../base64.cpp \
../main.cpp 

OBJS += \
./base64.o \
./main.o 

CPP_DEPS += \
./base64.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/home/fguo/Downloads/chilkat-9.5.0-x86_64-linux-gcc/include -I/home/fguo/Downloads/chilkat-9.5.0-x86_64-linux-gcc/lib -I/home/fguo/Downloads/thrift-0.8.0 -I/home/fguo/Downloads/thrift-0.8.0/lib/cpp/src -I/home/fguo/Downloads/thrift-0.8.0/lib/cpp -I"/home/fguo/workspace/gmailAPI" -O0 -g3 -Wall -c -fmessage-length=0 -std=gnu++0x -DHAVE_CONFIG_H -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


