
 #include <stdio.h>
 #include "pico/stdlib.h"
 #include "hardware/adc.h"
 
 /* Configuração da unidade de temperatura: 'C' para Celsius ou 'F' para Fahrenheit */
 #define TEMP_UNITS 'C'
 
 /* Função para ler a temperatura interna e convertê-la para °C ou °F */
 float ler_temperatura_interna(char unidade) {
     // Fator de conversão para um ADC de 12 bits (0 a 4095) com referência de 3.3V
     const float fator_conversao = 3.3f / (1 << 12);
     
     // Lê o valor bruto do ADC e converte para tensão
     int leitura_adc = adc_read();
     float tensao = leitura_adc * fator_conversao;
     
     // Fórmula para converter a tensão lida em temperatura em Celsius
     float tempC = 27.0f - (tensao - 0.706f) / 0.001721f;
     
     // Se a unidade solicitada for Fahrenheit, converte a temperatura
     if (unidade == 'F') {
         return tempC * 9.0f / 5.0f + 32.0f;
     }
     
     return tempC;
 }
 
 int main() {
     // Inicializa as funções padrão e de comunicação (USB/Serial)
     stdio_init_all();
 
 #ifdef PICO_DEFAULT_LED_PIN
     // Se houver LED padrão configurado, inicializa e define como saída
     gpio_init(PICO_DEFAULT_LED_PIN);
     gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
 #endif
 
     // Inicializa o ADC e habilita o sensor de temperatura interno
     adc_init();
     adc_set_temp_sensor_enabled(true);
     // Seleciona o canal 4, o qual está vinculado ao sensor de temperatura
     adc_select_input(4);
 
     while (true) {
         // Lê e converte a temperatura
         float temperatura = ler_temperatura_interna(TEMP_UNITS);
         // Imprime a temperatura no console
         printf("Temperatura: %.2f %c\n", temperatura, TEMP_UNITS);
 

 
         // Aguarda aproximadamente 1 segundo para a próxima leitura
         sleep_ms(990);
     }
 
     return 0;
 }
 