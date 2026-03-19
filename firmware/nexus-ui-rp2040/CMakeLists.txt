cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(nexus_ui_rp2040 C CXX ASM)
pico_sdk_init()

# 1. Adiciona o subdiretório com o nome exato da pasta
add_subdirectory(src/HOJA-LIB-RP2040)

add_executable(nexus_ui src/main.c)

# 2. Ajusta os diretórios de inclusão para MAIÚSCULAS
target_include_directories(nexus_ui PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/HOJA-LIB-RP2040/include
)

target_link_libraries(nexus_ui 
    pico_stdlib 
    hardware_i2c
    hoja_rp2040
)

pico_add_extra_outputs(nexus_ui)
pico_enable_stdio_usb(nexus_ui 1)