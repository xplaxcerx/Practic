#include "pico/stdlib.h"

int main() {
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (1) {
        gpio_put(LED_PIN, 1);
        sleep_ms(5000); // Подождать 5 секунд
        gpio_put(LED_PIN, 0);
        sleep_ms(5000);
    }

    return 0;
}
