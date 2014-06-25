################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../thrift/GmailService.cpp \
../thrift/gmail_Impl.cpp \
../thrift/gmail_constants.cpp \
../thrift/gmail_types.cpp 

OBJS += \
./thrift/GmailService.o \
./thrift/gmail_Impl.o \
./thrift/gmail_constants.o \
./thrift/gmail_types.o 

CPP_DEPS += \
./thrift/GmailService.d \
./thrift/gmail_Impl.d \
./thrift/gmail_constants.d \
./thrift/gmail_types.d 


# Each subdirectory must supply rules for building sources it contributes
thrift/%.o: ../thrift/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/home/fguo/Downloads/chilkat-9.5.0-x86_64-linux-gcc/include -I/home/fguo/Downloads/chilkat-9.5.0-x86_64-linux-gcc/lib -I/home/fguo/Downloads/thrift-0.8.0 -I/home/fguo/Downloads/thrift-0.8.0/lib/cpp/src -I/home/fguo/Downloads/thrift-0.8.0/lib/cpp -I"/home/fguo/workspace/gmailAPI" -O0 -g3 -Wall -c -fmessage-length=0 -std=gnu++0x -DHAVE_CONFIG_H -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


