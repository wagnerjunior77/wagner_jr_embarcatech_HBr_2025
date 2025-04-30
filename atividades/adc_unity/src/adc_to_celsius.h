#ifndef ADC_TO_CELSIUS_H
#define ADC_TO_CELSIUS_H

#include <stdint.h>

/**
 * Converte uma amostra de 12 bits do ADC interno (0-4095)
 * para temperatura em graus Celsius, usando a fórmula oficial
 * do RP2040 (Vref = 3,3 V).
 */
float adc_to_celsius(uint16_t adc_val);

#endif /* ADC_TO_CELSIUS_H */