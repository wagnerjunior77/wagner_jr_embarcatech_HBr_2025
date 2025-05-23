# ⏱️ Contador Decrescente com Interrupções (RP2040)

Projeto em C para microcontrolador RP2040 que implementa um contador decrescente controlado por **interrupções** e exibido em um **display OLED**. O sistema utiliza dois botões físicos conectados aos GPIOs do microcontrolador para controlar a lógica.

## 🎯 Objetivo

Criar um sistema embarcado que:

- Inicie uma contagem regressiva de 9 a 0 ao pressionar um botão (Botão A - GPIO5).
- Conte quantas vezes um segundo botão (Botão B - GPIO6) é pressionado **durante a contagem**.
- Exiba tudo no display OLED.
- Ignore interações fora do período ativo.

## ⚙️ Comportamento do Sistema

### 🔘 Botão A (GPIO5)

- Ao ser pressionado:
  - Reinicia a contagem regressiva a partir de **9**.
  - Zera o contador de cliques do Botão B.
  - Exibe os dois valores (contagem e cliques) no display.
  - Inicia o modo de contagem regressiva **ativa** (decrementando de 1 em 1 por segundo).

### 🔘 Botão B (GPIO6)

- Durante a contagem (de 9 até 0):
  - Cada clique incrementa um **contador de cliques**.
  - Esse número é exibido no OLED junto do contador principal.

- Após a contagem chegar a 0:
  - O sistema **congela**.
  - Novos cliques no Botão B são ignorados.
  - O display exibe:
    - `Contador: 0`
    - `Cliques: N` (número total registrado durante os 9 segundos)

### 🔁 Reinício

- Ao pressionar novamente o **Botão A**:
  - A contagem é reiniciada de 9.
  - O número de cliques do Botão B é zerado.
  - Todo o processo recomeça.

## 🧰 Tecnologias e Componentes

- Linguagem **C**
- **RP2040** (Raspberry Pi Pico ou similar)
- Display **OLED** (via I2C)
- **Botões físicos** em GPIO5 (Botão A) e GPIO6 (Botão B)
- Uso de **interrupções GPIO**

## 📝 Observações

- O uso de interrupções garante resposta rápida e eficiente aos eventos dos botões.
- Ideal para fins didáticos e projetos introdutórios de sistemas embarcados.
- O projeto pode ser expandido para incluir buzzer, LEDs de status ou comunicação com outros módulos.