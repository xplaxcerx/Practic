#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/time.h"

const uint LED_PINS[] = {PICO_DEFAULT_LED_PIN, 2, 3}; // Пины светодиодов
const uint BUTTON_PIN = 3; // Пин кнопки (смены светодиода)

volatile bool button_pressed = false;

void button_isr() {
    button_pressed = true;
    // Сбросить прерывание
    gpio_acknowledge_irq(BUTTON_PIN, gpio_irq_x);
}

int main() {
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    for (int i = 0; i < 3; i++) {
        gpio_init(LED_PINS[i]);
        gpio_set_dir(LED_PINS[i], GPIO_OUT);
    }

    // Настроить аппаратное прерывание
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_RISE, true, &button_isr);

    int current_led = 0;

    while (1) {
        if (button_pressed) {
            gpio_put(LED_PINS[current_led], 1);
            sleep_ms(1000); // Подождать секунду
            gpio_put(LED_PINS[current_led], 0);
            current_led = (current_led + 1) % 3;
            button_pressed = false;
        }
    }

    return 0;
}
