#ifndef HAL_LED_H
#define HAL_LED_H

/* Inicializa a HAL (chama o driver internamente). */
int hal_led_init(void);

/* Alterna estado (on/off) a cada chamada. */
void hal_led_toggle(void);

#endif /* HAL_LED_H */