################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ExactMatcher.cpp \
../src/multisearch.cpp \
../src/rabinhash.cpp 

OBJS += \
./src/ExactMatcher.o \
./src/multisearch.o \
./src/rabinhash.o 

CPP_DEPS += \
./src/ExactMatcher.d \
./src/multisearch.d \
./src/rabinhash.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


