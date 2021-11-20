#include "ledblink.h"

esp_err_t enable_led_blink()
{
    esp_err_t ret;
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = ((1ULL << LED_1) | (1ULL << LED_2) | (1ULL << LED_3));
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    return ret;
}

led_blink set_ledblink()
{
    set_ledblink.ledblink_1 = gpio_set_level(LED_1, 1);
    set_ledblink.ledblink_2 = gpio_set_level(LED_2, 1);
    set_ledblink.ledblink_3 = gpio_set_level(LED_3, 1);
    return set_ledblink;
}
