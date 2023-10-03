#include "pico/stdlib.h"
#include "hardware/timer.h"

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

    // Настроить аппаратный таймер
    uint32_t timer_us = 1000000; // 1 секунда
    uint32_t timer_ms = 1000;    // 1 миллисекунда
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_RISE, true, NULL);
    timer_config_t config = timer_get_default_config();
    timer_init(timer0, &config);
    timer_set_alarm_value(timer0, timer_us);
    timer_set_irq_enabled(timer0, true);
    irq_set_exclusive_handler(TIMER_IRQ_0, timer_handler);
    irq_set_enabled(TIMER_IRQ_0, true);

    while (1) {
        // Главный цикл выполняется по прерыванию от таймера
        __wfi();
        gpio_put(LED_PINS[current_led], 1);
        sleep_ms(1000); // Подождать секунду
        gpio_put(LED_PINS[current_led], 0);
        current_led = (current_led + 1) % 3;
    }

    return 0;
}

void timer_handler() {
    // Обработчик прерывания от таймера
    gpio_put(PICO_DEFAULT_LED_PIN, 1);
    sleep_ms(100); // Подождать 100 миллисекунд
    gpio_put(PICO_DEFAULT_LED_PIN, 0);
    sleep_ms(100);
}
