# 🌡️ Leitura de Temperatura Interna no Raspberry Pi Pico W

Este projeto demonstra como utilizar o **sensor de temperatura interno** do chip **RP2040** (Raspberry Pi Pico ou Pico W) para ler a temperatura em graus Celsius (ou Fahrenheit), com melhorias como **filtro de média**, **offset de calibração** e **teste unitário com Unity**.

---

## 🧠 Objetivos

✅ Ler a temperatura interna com o ADC do RP2040  
✅ Aplicar média de múltiplas amostras para reduzir ruído  
✅ Converter os valores ADC para temperatura em °C com base na fórmula oficial  
✅ Testar a conversão com um valor simulado usando a biblioteca Unity  
✅ Mostrar o valor no terminal serial de forma suave e controlada

---

## 📂 Estrutura do Projeto

```
📁 src/
├── adc_to_celsius.c       # Função que converte ADC para temperatura
├── adc_to_celsius.h       # Header da função de conversão
├── test_adc_to_celsius.c  # Teste unitário com Unity
├── unity.c                # Biblioteca Unity (testes)
├── unity.h
└── adc_demo.c             # Código principal que roda no Pico
```

---

## ⚙️ Requisitos

- Raspberry Pi Pico ou Pico W
- Raspberry Pi Pico SDK
- arm-none-eabi-gcc
- CMake ≥ 3.13
- (opcional) VS Code com extensões do Pico

---

## 🔧 Como Compilar

1. Baixe apenas esta pasta do projeto (sem o repositório todo):

👉 Acesse: https://minhaskamal.github.io/DownGit/

Cole este link no campo: https://github.com/wagnerjunior77/wagner_jr_embarcatech_HBr_2025/tree/main/atividades/adc_unity

Clique em “Download” para baixar um .zip contendo somente esta atividade.

2. Configure o CMake e compile:

```bash
mkdir build && cd build
cmake ..
make -j
```

Você terá dois arquivos `.uf2`:

- `adc_demo.uf2` → mostra a temperatura real no terminal
- `adc_tests.uf2` → executa o teste unitário no Pico

---

## 🔬 Teste Unitário

O teste simula uma leitura ADC de aproximadamente 0,706 V (valor de referência para 27 °C) e valida se a função `adc_to_celsius()` retorna corretamente:

```text
Unity test run 1 of 1
test_adc_706mV_returns_27C: PASS
-----------------------
1 Tests 0 Failures 0 Ignored
OK
```

Grave `adc_tests.uf2` no Pico e abra o monitor serial (115200 baud) para ver o resultado.

---

## 📈 Execução (adc_demo)

Grave `adc_demo.uf2` no Pico. Ele vai:

- Fazer 16 leituras do ADC
- Tirar a média (ignorando a 1ª leitura)
- Converter para temperatura com a fórmula oficial
- Imprimir no terminal serial a cada 1 segundo

Exemplo de saída:

```text
Temperatura: 33.75 C
Temperatura: 34.06 C
Temperatura: 33.88 C
```

---

## 🛠️ Personalizações

Você pode modificar as seguintes constantes em `adc_demo.c`:

| Constante         | Efeito                                    |
|------------------|--------------------------------------------|
| `NUM_SAMPLES`     | Número de amostras para média (ex.: 16)   |
| `PRINT_PERIOD_MS` | Intervalo de tempo entre prints           |
| `TEMP_UNITS`      | `'C'` ou `'F'` para escolher a unidade     |
| `TEMP_OFFSET_C`   | Corrigir leitura com um termômetro externo|

---

## 📘 Referência da Fórmula

Fórmula oficial da Raspberry Pi para conversão de tensão em temperatura:

```
T(°C) = 27 - (Vtemp - 0.706) / 0.001721
```

---

