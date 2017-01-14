cmake_minimum_required(VERSION 3.6)
project(chinookTest1)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 14)

# Set C++ Compiler to FRC Toolchains
set(CMAKE_CXX_COMPILER /usr/bin/arm-frc-linux-gnueabi-g++)

# Include C++ headers files for WPILib
include_directories($ENV{HOME}/wpilib/cpp/current/include)

# # Set include header files path
# set(INCDIR "-I$ENV{HOME}/wpilib/cpp/current/include")

# Set C++ Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -W -std=c++11 -fPIC") # change: remove ${INCDIR}

# Set LFLAGS
set(CMAKE_EXE_LINKER_FLAGS "$ENV{HOME}/wpilib/cpp/current/lib -lwpi")

# Set source files path
set(SOURCE_FILES src/ChinookTest.cpp)

add_executable(untitled ${SOURCE_FILES})


#add_custom_target(chinookTest1 COMMAND make -C ${chinookTest1_SOURCE_DIR}
#        CLION_EXE_DIR=${PROJECT_BINARY_DIR})
