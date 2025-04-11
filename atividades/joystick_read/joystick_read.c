

 #include <stdio.h>
 #include "pico/stdlib.h"
 #include "hardware/adc.h"
 
 int main() {
     // Inicializa o sistema padrão (USB/serial) e o ADC
     stdio_init_all();
     adc_init();
 
     // Configura os pinos dos canais ADC para o joystick
     adc_gpio_init(26);  // Geralmente associado ao eixo Y (canal 0)
     adc_gpio_init(27);  // Geralmente associado ao eixo X (canal 1)
 
     while (1) {
         // Lê o valor do eixo Y:
         adc_select_input(0);  // Seleciona o canal 0 (GPIO 26)
         uint16_t adc_y = adc_read();
 
         // Lê o valor do eixo X:
         adc_select_input(1);  // Seleciona o canal 1 (GPIO 27)
         uint16_t adc_x = adc_read();
 
         // Exibe os valores lidos no terminal
         printf("Joystick -> X: %u  |  Y: %u\n", adc_x, adc_y);
 
         // Aguarda 100 ms antes da próxima leitura
         sleep_ms(100);
     }
     return 0;
 }
 