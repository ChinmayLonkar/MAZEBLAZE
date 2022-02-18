#include "mazeblaze.h"

void app_main()
{
    ESP_ERROR_CHECK(enable_led());
    ESP_ERROR_CHECK(enable_motor_driver());


    while (1)
    {
        if (gpio_get_level(DEBUG_SWITCH) == 0){
        // set_led_on();
        // vTaskDelay(100 / portTICK_RATE_MS);
        set_led_off();
        vTaskDelay(100 / portTICK_RATE_MS);
    }}
}
