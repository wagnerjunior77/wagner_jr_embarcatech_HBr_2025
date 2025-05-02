#include "hal_led.h"
#include "led_embutido.h"
#include <stdbool.h>

static bool estado = false;   // estado atual do LED

int hal_led_init(void) {
    estado = false;
    return led_embutido_init();   // repassa erro/sucesso
}

void hal_led_toggle(void) {
    estado = !estado;
    led_embutido_write(estado);
}