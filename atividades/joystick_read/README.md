# 🎮 Leitor de Joystick Analógico - RP2040

Projeto em C que realiza a leitura dos **valores analógicos de um joystick** conectado ao microcontrolador RP2040. Os dados dos eixos X e Y são lidos via ADC e exibidos no terminal serial em tempo real.

## 🎯 Objetivo

- Ler as posições dos eixos X e Y de um joystick analógico.
- Utilizar os canais ADC do RP2040 para capturar os sinais.
- Exibir os valores no terminal serial via USB.

## ⚙️ Funcionamento

1. Inicializa os periféricos padrão e o ADC.
2. Configura os GPIOs 26 e 27 como entradas analógicas (ADC0 e ADC1).
3. No loop principal:
   - Lê o valor do canal 0 (eixo Y).
   - Lê o valor do canal 1 (eixo X).
   - Exibe os dois valores formatados no terminal.
   - Espera 100ms antes da próxima leitura.

## 🧰 Mapeamento de Pinos

| Eixo     | GPIO | Canal ADC |
|----------|------|-----------|
| Y (Vertical) | 26   | ADC 0     |
| X (Horizontal) | 27   | ADC 1     |

## 🛠️ Requisitos

- Placa com **RP2040** (ex: Raspberry Pi Pico)
- Joystick analógico (2 eixos)
- SDK do Pico configurado
- Terminal serial (Thonny, minicom, PuTTY etc.)

## 💡 Observações

- Os valores lidos variam de **0 a 4095** (ADC de 12 bits).
- O valor central (neutro) do joystick geralmente fica em torno de **2048**.
- Pode ser adaptado para jogos, navegação em menus com joystick ou controle de robôs.

## 📂 Estrutura básica do projeto

- `main.c` - Código principal de leitura do joystick
- `CMakeLists.txt` - Configuração de build com Pico SDK

---
Esse projeto é uma ótima introdução à leitura de sinais analógicos com o RP2040!