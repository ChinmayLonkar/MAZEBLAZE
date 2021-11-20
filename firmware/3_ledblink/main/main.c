#include "ledblink.h"

void app_main()
{
    ESP_ERROR_CHECK(enable_led_blink());

    while (1)
    {
        led_blink set_ledblink();
    
        vTaskDelay(100 / portTICK_RATE_MS);
    }
}
