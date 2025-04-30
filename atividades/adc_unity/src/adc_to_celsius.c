#include "adc_to_celsius.h"

float adc_to_celsius(uint16_t adc_val)
{
    const float vref        = 3.3f;          // tensão de referência
    const float conv_factor = vref / (1 << 12); // 3.3 V / 4096 ≈ 0.000805664 V por LSB
    float v_temp            = adc_val * conv_factor;

    /* Fórmula da documentação:
       T(°C) = 27 − (Vtemp − 0.706) / 0.001721            */
    return 27.0f - (v_temp - 0.706f) / 0.001721f;
}
