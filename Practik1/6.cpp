#include "pico/stdlib.h"
#include "hardware/pwm.h"

int main() {
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    const uint POTENTIOMETER_PIN = 26; // Пин, к которому подключен потенциометр
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Настроить PWM на пине
    pwm_gpio_init(PWM_GPIO, POTENTIOMETER_PIN);
    uint slice_num = pwm_gpio_to_slice_num(POTENTIOMETER_PIN);
    pwm_set_wrap(slice_num, 255); // 8-битное ШИМ
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 0);
    pwm_set_enabled(slice_num, true);

    while (1) {
        // Прочитать значение с потенциометра и установить его в качестве яркости светодиода
        uint16_t pot_value = adc_read(); // Прочитать значение с потенциометра
        pwm_set_chan_level(slice_num, PWM_CHAN_A, pot_value);
    }

    return 0;
}
