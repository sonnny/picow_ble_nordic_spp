
cmake_minimum_required(VERSION 3.12)
set(PICO_SDK_PATH "/home/sonny/pico/pico-sdk")
set(PICO_BOARD "pico_w")
include("${PICO_SDK_PATH}/external/pico_sdk_import.cmake")

project(blink C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_PLATFORM rp2040)
set(PICO_COMPILER "pico_arm_gcc")
set(CMAKE_BUILD_TYPE Release)
pico_sdk_init()
add_executable(blink
    blink.c
	)
target_link_libraries(blink
    pico_stdlib
    pico_btstack_ble
    pico_btstack_cyw43
    pico_cyw43_arch_none
    )
#pico_enable_stdio_usb(blink 0)
#pico_enable_stdio_uart(blink 1)
target_include_directories(blink PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    )
pico_btstack_make_gatt_header(blink PRIVATE "${CMAKE_CURRENT_LIST_DIR}/mygatt.gatt")
pico_add_extra_outputs(blink)
