#include "pico/stdlib.h"

int main() {
    const uint LED_PINS[] = {PICO_DEFAULT_LED_PIN, 2, 3}; // Пины светодиодов
    const uint BUTTON_PIN = 3; // Пин кнопки (смены светодиода)
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    
    for (int i = 0; i < 3; i++) {
        gpio_init(LED_PINS[i]);
        gpio_set_dir(LED_PINS[i], GPIO_OUT);
    }

    int current_led = 0;

    while (1) {
        if (gpio_get(BUTTON_PIN)) {
            gpio_put(LED_PINS[current_led], 1);
            sleep_ms(1000); // Подождать секунду
            gpio_put(LED_PINS[current_led], 0);
            current_led = (current_led + 1) % 3;
        }
    }

    return 0;
}
