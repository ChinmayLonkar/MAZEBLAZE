
#include "mazeblaze.h"

void app_main(void)
{
    ESP_ERROR_CHECK(enable_lsa());

    while (1)
    {
        printf("%d %d %d %d %d \n", get_reading_lsa().lsa_reading[0], get_reading_lsa().lsa_reading[1], get_reading_lsa().lsa_reading[2], get_reading_lsa().lsa_reading[3],get_reading_lsa().lsa_reading[4]);
        vTaskDelay(100 / portTICK_RATE_MS);
    }
}
