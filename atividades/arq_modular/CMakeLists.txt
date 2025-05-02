# =====================================================================
#  CMakeLists.txt – Projeto “arq_modular”
#  Estrutura:
#     app/arq_modular.c              → lógica da aplicação
#     drivers/led_embutido.c  → driver de hardware
#     hal/hal_led.c           → camada HAL
#     include/*.h             → cabeçalhos públicos
# =====================================================================

cmake_minimum_required(VERSION 3.13)

#-----------------------------------------------------------------------
# Configurações gerais
#-----------------------------------------------------------------------
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#-----------------------------------------------------------------------
# (trecho gerado pela extensão VS Code do Pico – mantenha intocado)
#-----------------------------------------------------------------------
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
#-----------------------------------------------------------------------

# Alvo: Raspberry Pi Pico W
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Importa o SDK
include(pico_sdk_import.cmake)

project(arq_modular C CXX ASM)
pico_sdk_init()

#-----------------------------------------------------------------------
# Diretório global de headers
#-----------------------------------------------------------------------
include_directories(include)

#-----------------------------------------------------------------------
# DRIVERS
#-----------------------------------------------------------------------

# --- Driver: LED embutido ---
add_library(driver_led STATIC
    drivers/led_embutido.c
)

target_link_libraries(driver_led
    PUBLIC                 # ←  PUBLIC (ou INTERFACE)
        pico_stdlib
        pico_cyw43_arch_none   # ← lib cyw43
)


#-----------------------------------------------------------------------
# HAL
#-----------------------------------------------------------------------
add_library(hal_led STATIC
    hal/hal_led.c
)
target_link_libraries(hal_led
    driver_led         # depende do driver
)

#-----------------------------------------------------------------------
# APLICAÇÃO
#-----------------------------------------------------------------------
add_executable(arq_modular
    app/arq_modular.c
)

# Nome e versão exibidos via USB - opcional
pico_set_program_name(arq_modular "arq_modular")
pico_set_program_version(arq_modular "0.1")

# STDIO (USB e UART) – habilite/desabilite conforme precisar
pico_enable_stdio_uart(arq_modular 1)
pico_enable_stdio_usb(arq_modular 1)

# Vincula bibliotecas necessárias
target_link_libraries(arq_modular
    pico_stdlib
    hal_led            # usa a HAL (que já puxa o driver)
)

# Gera UF2, ELF, map etc.
pico_add_extra_outputs(arq_modular)
