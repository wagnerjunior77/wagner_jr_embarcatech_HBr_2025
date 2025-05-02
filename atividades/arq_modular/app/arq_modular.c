#include "pico/stdlib.h"
#include "hal_led.h"

int main() {
    stdio_init_all();

    if (hal_led_init() != 0) {
        return -1;          // aborta se CYW43 falhar
    }

    while (true) {
        hal_led_toggle();
        sleep_ms(500);
    }
}
