
 #include "pico/stdlib.h"
 #include "hardware/gpio.h"
 #include "hardware/irq.h"
 #include "pico/time.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
 // headers do display OLED
 #include "src/ssd1306.h"
 #include "src/ssd1306_i2c.h"
 #include "src/ssd1306_font.h"
 
 // Definições dos botões e pinos
 #define BUTTON_A 5  // Reinicia/começa a contagem
 #define BUTTON_B 6  // Contabiliza cliques durante a contagem
 
 // Parâmetros da contagem
 #define CONTADOR_INICIAL 9
 
 // Protótipos de funções
 void update_display(void);
 bool countdown_timer_callback(struct repeating_timer *rt);
 void button_irq_callback(uint gpio, uint32_t events);
 
 // Variáveis globais (declaradas como voláteis pois são modificadas em interrupções)
 volatile int countdown_value = 0;
 volatile int b_press_count = 0;
 volatile bool countdown_active = false;
 // Flag para indicar que o display precisa ser atualizado no loop principal
 volatile bool update_display_flag = false;
 
 // Ponteiro para o timer (usado para cancelar quando a contagem terminar)
 struct repeating_timer countdown_timer;
 
 // Objeto global do display OLED
 ssd1306_t disp;
 
 // Função para atualizar o display OLED com os valores atuais
 void update_display(void) {
     char linha1[32], linha2[32];
     // Formata as strings: uma linha para o contador e outra para os cliques
     snprintf(linha1, sizeof(linha1), "Contador: %d", countdown_value);
     snprintf(linha2, sizeof(linha2), "Botao B: %d", b_press_count);
     
     ssd1306_clear(&disp);
     // Exibe na posição
     ssd1306_draw_string(&disp, 0, 0, 1, linha1);
     ssd1306_draw_string(&disp, 0, 16, 1, linha2);
     ssd1306_show(&disp);
 }
 
 // Callback do timer, executado a cada 1000 ms (1 segundo)
 // É chamado no contexto de interrupção;
 bool countdown_timer_callback(struct repeating_timer *rt) {
     if (countdown_active) {
         if (countdown_value > 0) {
             countdown_value--;
         }
         update_display_flag = true; // sinaliza que o display deve ser atualizado
         
         // Se a contagem chegou a 0, encerra o timer e desabilita a contagem
         if (countdown_value <= 0) {
             countdown_active = false;
             return false;   // retornar false cancela o timer repetitivo
         }
     }
     return true; // mantém o timer ativo enquanto countdown_active
 }
 
 // Callback das interrupções dos botões
 void button_irq_callback(uint gpio, uint32_t events) {
    static absolute_time_t last_press_a = {0};
    static absolute_time_t last_press_b = {0};
    absolute_time_t now = get_absolute_time();

    if (gpio == BUTTON_A) {
        // Se ocorrer outro evento em menos de 200 ms, ignora
        if (absolute_time_diff_us(last_press_a, now) < 200000) return;
        last_press_a = now;

        // Reinicia a contagem e ativa o timer
        countdown_value = CONTADOR_INICIAL;
        b_press_count = 0;
        countdown_active = true;
        update_display_flag = true;
        // Inicia o timer para contagem regressiva
        add_repeating_timer_ms(1000, countdown_timer_callback, NULL, &countdown_timer);
    } else if (gpio == BUTTON_B) {
        if (absolute_time_diff_us(last_press_b, now) < 200000) return;
        last_press_b = now;

        if (countdown_active) {
            b_press_count++;
            update_display_flag = true;
        }
    }
}
 
 int main() {
     // Inicializações padrão
     stdio_init_all();
     sleep_ms(1000);
     printf("Iniciando sistema de contagem com interrupcoes\n");
     
     // Inicializa o display OLED 
     // funções de inicialização
     i2c_init(i2c1, 400000);
     gpio_set_function(14, GPIO_FUNC_I2C); // SDA
     gpio_set_function(15, GPIO_FUNC_I2C); // SCL
     gpio_pull_up(14);
     gpio_pull_up(15);
     
     disp.external_vcc = false;
     if (!ssd1306_init(&disp, 128, 64, 0x3C, i2c1)) {
          printf("Erro ao inicializar o OLED\n");
          return 1;
     }
     ssd1306_clear(&disp);
     update_display();
     
     // Configura os pinos dos botões e registra a rotina de interrupção
     gpio_init(BUTTON_A);
     gpio_set_dir(BUTTON_A, GPIO_IN);
     gpio_pull_up(BUTTON_A);
     
     gpio_init(BUTTON_B);
     gpio_set_dir(BUTTON_B, GPIO_IN);
     gpio_pull_up(BUTTON_B);
     
     // Registra callback para ambos os botões.
     // A função gpio_set_irq_enabled_with_callback permite tratar mais de um pino com o mesmo callback.
     gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_irq_callback);
     gpio_set_irq_enabled(BUTTON_B, GPIO_IRQ_EDGE_FALL, true);
     // Como registramos o callback acima para o BUTTON_A, este callback será chamado para ambos os pinos.
 
     // Loop principal: atualiza o display se necessário
     while (true) {
         if (update_display_flag) {
             update_display();
             update_display_flag = false;
         }
         sleep_ms(50); // pequena espera para reduzir uso da CPU
     }
     
     return 0;
 }
 