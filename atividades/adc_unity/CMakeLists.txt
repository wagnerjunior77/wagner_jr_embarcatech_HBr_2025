# ---------------------------------------------------------------------------
#  Projeto:     ADC + Unity (Raspberry Pi Pico W)
#  Gera dois executáveis:
#   - adc_demo  → roda o firmware principal (adc_unity.c)
#   - adc_tests → roda os testes unitários (Unity)
# ---------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.13)

# Padrões de linguagem
set(CMAKE_C_STANDARD   11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# == (trecho gerado pela extensão VS Code - deixe como está) =================
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion        2.1.1)
set(toolchainVersion  14_2_Rel1)
set(picotoolVersion   2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ============================================================================

set(PICO_BOARD pico_w CACHE STRING "Board type")
include(pico_sdk_import.cmake)           # puxa o SDK
project(adc_unity C CXX ASM)
pico_sdk_init()

# Caminho comum de includes (headers na pasta src/)
set(PROJ_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

# ---------------------------------------------------------------------------
# 1) Firmware normal – lê o sensor e printa temperatura
# ---------------------------------------------------------------------------
add_executable(adc_demo
        adc_unity.c                 # main original
        src/adc_to_celsius.c)       # função compartilhada

pico_set_program_name   (adc_demo "adc_demo")
pico_set_program_version(adc_demo "0.1")

pico_enable_stdio_uart(adc_demo 1)
pico_enable_stdio_usb (adc_demo 1)

target_include_directories(adc_demo PRIVATE ${PROJ_SRC_DIR})
target_link_libraries   (adc_demo pico_stdlib hardware_adc)
pico_add_extra_outputs  (adc_demo)

# ---------------------------------------------------------------------------
# 2) Executável de testes – somente Unity
# ---------------------------------------------------------------------------
add_executable(adc_tests
        src/test_adc_to_celsius.c
        src/adc_to_celsius.c
        src/unity.c)

pico_set_program_name   (adc_tests "adc_tests")
pico_set_program_version(adc_tests "0.1")

pico_enable_stdio_uart(adc_tests 1)   # precisa do serial para imprimir PASS/FAIL
pico_enable_stdio_usb (adc_tests 1)

target_include_directories(adc_tests PRIVATE ${PROJ_SRC_DIR})
target_link_libraries   (adc_tests pico_stdlib)     # sem hardware_adc: testes não usam ADC real
pico_add_extra_outputs  (adc_tests)

# ---------------------------------------------------------------------------
# Fim do arquivo
# ---------------------------------------------------------------------------
