# This is not complete file. It has bare minimum to use this project with CLion.

cmake_minimum_required(VERSION 3.8)
project(esp_ex)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_C_COMPILER "$ENV{HOME}/lib/esp-open-sdk/xtensa-lx106-elf/bin/xtensa-lx106-elf-gcc")
SET(CMAKE_CXX_COMPILER "$ENV{HOME}/lib/esp-open-sdk/xtensa-lx106-elf/bin/xtensa-lx106-elf-g++")

if(NOT DEFINED ENV{ESP_OPEN_SDK})
    message("Seting ESP_OPEN_SDK to $ENV{HOME}/lib/esp-open-sdk")
    set(ENV{ESP_OPEN_SDK} "$ENV{HOME}/lib/esp-open-sdk")
endif()

message("Open SDK at $ENV{ESP_OPEN_SDK}")

include_directories($ENV{ESP_OPEN_SDK}/sdk/include)

include_directories(lib/uart/include)
include_directories(lib/easygpio/include)
include_directories(include)

set(HEADER_FILES
        lib/uart/include/uart.h
        lib/uart/include/uart_register.h
        lib/easygpio/include/easygpio/easygpio.h

        examples/blink/include/user_config.h
        examples/gpio_itr/include/user_config.h
        examples/hello_world/include/user_config.h
)

set(SOURCE_FILES
        examples/blink/user/main.c
        examples/gpio_itr/user/main.c
        examples/hello_world/user/main.c

        lib/uart/uart.c
        lib/easygpio/easygpio.c

)

add_library(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})