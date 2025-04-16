# 🌡️ Leitor de Temperatura Interna - RP2040

Este projeto em C realiza a leitura da **temperatura interna do chip RP2040**, utilizando seu sensor embutido. O valor é lido via ADC, convertido para Celsius ou Fahrenheit, e exibido no terminal serial.

## 🎯 Objetivo

- Ler o sensor de temperatura interna do microcontrolador RP2040.
- Exibir os dados no terminal em tempo real (via USB/serial).
- Permitir seleção da unidade de exibição (`°C` ou `°F`).

## ⚙️ Funcionamento

O programa executa os seguintes passos:

1. Inicializa o sistema e o ADC.
2. Habilita o sensor de temperatura interno (canal ADC 4).
3. Converte o valor de ADC para tensão.
4. Usa a fórmula fornecida pela Raspberry Pi para converter tensão em temperatura Celsius.
5. Se configurado, converte o valor para Fahrenheit.
6. Exibe o valor no terminal serial a cada segundo.

## 🧪 Fórmulas utilizadas

### 🔹 Conversão ADC → Tensão

```
tensao = leitura_adc * (3.3 / 4096)
```

### 🔹 Tensão → Temperatura (Celsius)

```
tempC = 27 - (tensao - 0.706) / 0.001721
```

### 🔹 Celsius → Fahrenheit (se ativado)

```
tempF = tempC * 9 / 5 + 32
```

## 🔧 Configuração

Você pode definir a unidade de temperatura alterando esta linha no código:

```c
#define TEMP_UNITS 'C' // ou 'F'
```

## 🛠️ Requisitos

- Placa com RP2040 (ex: Raspberry Pi Pico)
- SDK do Pico configurado
- Terminal serial (minicom, PuTTY, Thonny, etc.)

## 💡 Observações

- A precisão do sensor de temperatura interno não é ideal para medições ambientais, mas serve bem para fins didáticos e de monitoramento térmico básico.
- Pode ser expandido para mostrar os dados em um display OLED, enviar via Bluetooth, etc.

## 📂 Estrutura básica do projeto

- `main.c` - Código principal com leitura e conversão de temperatura
- `CMakeLists.txt` - Configuração de build com Pico SDK
