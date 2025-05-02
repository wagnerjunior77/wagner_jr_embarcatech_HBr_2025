#ifndef LED_EMBUTIDO_H
#define LED_EMBUTIDO_H

#include <stdbool.h>

/* Inicializa CYW43 e prepara o LED. Retorna 0 em sucesso, -1 em erro. */
int led_embutido_init(void);

/* Escreve no LED: true = liga, false = desliga */
void led_embutido_write(bool on);

#endif /* LED_EMBUTIDO_H */