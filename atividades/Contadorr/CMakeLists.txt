# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# PICO_BOARD e includes do pico_sdk
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Importa o Pico SDK (precisa do pico_sdk_import.cmake na mesma pasta)
include(pico_sdk_import.cmake)

# Nome do projeto
project(contador C CXX ASM)

# Inicializa o SDK
pico_sdk_init()

# Cria o executável, listando o arquivo principal + drivers
add_executable(contador
    Contadorr.c
    src/ssd1306_i2c.c
    # Se tiver outro .c (ex: ssd1306.c), pod botar aqui
)

# Define nome e versão do executável
pico_set_program_name(contador "contador")
pico_set_program_version(contador "0.1")

# Configura console via USB/UART
pico_enable_stdio_uart(contador 0)
pico_enable_stdio_usb(contador 1)

# Vincula bibliotecas necessárias (std, hardware i2c, etc.)
target_link_libraries(contador
    pico_stdlib
    hardware_i2c
)

# Inclui diretórios que contêm cabeçalhos .h
target_include_directories(contador PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# Gera arquivo .uf2, .hex etc. ao compilar
pico_add_extra_outputs(contador)
