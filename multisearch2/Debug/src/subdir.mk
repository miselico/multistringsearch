################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ExactMatcher.cpp \
../src/ExactMatcher2.cpp \
../src/multisearch.cpp \
../src/rabinhash.cpp 

OBJS += \
./src/ExactMatcher.o \
./src/ExactMatcher2.o \
./src/multisearch.o \
./src/rabinhash.o 

CPP_DEPS += \
./src/ExactMatcher.d \
./src/ExactMatcher2.d \
./src/multisearch.d \
./src/rabinhash.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -D__GXX_EXPERIMENTAL_CXX0X__ -D__cplusplus=201103L -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


