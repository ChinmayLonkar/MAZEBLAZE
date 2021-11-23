#include "mazeblaze.h"

void app_main()
{
    ESP_ERROR_CHECK(enable_led());

    while (1)
    {
        set_led_on();
        vTaskDelay(100 / portTICK_RATE_MS);
        set_led_off();
        vTaskDelay(100 / portTICK_RATE_MS);
    }
}
