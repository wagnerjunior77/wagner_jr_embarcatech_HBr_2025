#include "unity.h"
#include "adc_to_celsius.h"
#include "pico/stdlib.h"

/* Configurações do Unity (não precisamos de set-up/tear-down para este teste) */
void setUp(void)   {}
void tearDown(void){}

static const float EPSILON = 0.2f;   // margem de erro aceitável (±0,2 °C)

/* 0,706 V → amostra ADC ≈ 0.706 / (3.3/4096) ≈ 876 */
void test_adc_706mV_returns_27C(void)
{
    uint16_t adc_sample = 876;   // valor “mágico” que deve dar 27 °C
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 27.0f, adc_to_celsius(adc_sample));
}

int main(void)
{
    stdio_init_all();         //  <-- inicializa USB e/ou UART
    sleep_ms(1500);
    
    // espera até o cabo USB ser enumerado
    while (!stdio_usb_connected()) { tight_loop_contents(); }

    printf(">> Boot ok, rodando testes...\n");
    
    UNITY_BEGIN();
    RUN_TEST(test_adc_706mV_returns_27C);
    return UNITY_END();
}
