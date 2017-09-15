cmake_minimum_required(VERSION 3.8)
project(VendingMachine)

set(CMAKE_C_STANDARD 99)

file(GLOB SOURCES */*.h */*.c *.h *.c)
add_executable(VendingMachine ${SOURCES})