cmake_minimum_required(VERSION 3.25)
project(arduino_test)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_GENERATOR_PLATFORM x86)

set(SOURCES
        src/arduino/arduino.cpp)

add_executable(arduino_test src/main.cpp src/arduino/arduino.cpp)
