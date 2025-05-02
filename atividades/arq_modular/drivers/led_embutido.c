#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "led_embutido.h"

int led_embutido_init(void) {
    if (cyw43_arch_init()) {
        return -1;          // falhou inicialização do Wi-Fi chip
    }
    /* Garante que o LED começa apagado */
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    return 0;
}

void led_embutido_write(bool on) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on ? 1 : 0);
}
