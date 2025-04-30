/*
 * Leitor de temperatura interna – versão filtrada + taxa de impressão controlada
 * Raspberry Pi Pico / RP2040
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

/* ---------- Configurações ---------- */
#define TEMP_UNITS      'C'         // 'C' ou 'F'
#define NUM_SAMPLES     16          // quantas leituras médias
#define PRINT_PERIOD_MS 1000        // intervalo entre prints
#define TEMP_OFFSET_C   0.0f        // calibração manual (+/- ºC)

/* ---------- Converte ADC -> ºC ---------- */
static float adc_to_celsius(uint16_t raw)
{
    const float vref  = 3.3f;
    const float lsb   = vref / (1 << 12);        // 3.3 / 4096
    float v_temp      = raw * lsb;
    float temp_c      = 27.0f - (v_temp - 0.706f) / 0.001721f;
    return temp_c + TEMP_OFFSET_C;               // aplica offset de calibração
}

/* ---------- Lê várias amostras e faz média ---------- */
static float ler_temp_media_celsius(void)
{
    /* descarta a 1ª amostra (às vezes vem “suja”) */
    (void)adc_read();

    uint32_t soma = 0;
    for (int i = 0; i < NUM_SAMPLES; ++i) {
        soma += adc_read();
        sleep_us(25);                 // pequeno delay entre amostras
    }
    uint16_t media = soma / NUM_SAMPLES;
    return adc_to_celsius(media);
}

/* ---------- Main ---------- */
int main(void)
{
    stdio_init_all();

    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);              // canal do sensor interno

    absolute_time_t proxima_impressao = make_timeout_time_ms(0);

    while (true) {

        float temp_c = ler_temp_media_celsius();

        /* Só imprime quando chegar a hora */
        if (absolute_time_diff_us(get_absolute_time(), proxima_impressao) <= 0) {

            if (TEMP_UNITS == 'F')
                printf("Temperatura: %.2f F\n", temp_c * 9.0f/5.0f + 32.0f);
            else
                printf("Temperatura: %.2f C\n", temp_c);

            /* agenda a próxima impressão */
            proxima_impressao = delayed_by_ms(proxima_impressao, PRINT_PERIOD_MS);
        }

        /* Pequeno repouso p/ não gastar CPU a toa */
        sleep_ms(10);
    }
}
