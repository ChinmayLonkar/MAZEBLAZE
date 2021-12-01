#include "led.h"


esp_err_t enable_led()
{
    esp_err_t ret;
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << END_LED);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    ret = gpio_config(&io_conf);
    return ret;
}

esp_err_t set_led_on()
{
    esp_err_t ret;
    ret = gpio_set_level(END_LED, 1);
    return ret;
}

esp_err_t set_led_off()
{
    esp_err_t ret;
    ret = gpio_set_level(END_LED, 0);
    return ret;
}
