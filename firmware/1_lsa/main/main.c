
#include "mazeblaze.h"

void app_main(void)
{
    ESP_ERROR_CHECK(enable_lsa());
    ESP_ERROR_CHECK(enable_motor_driver());
   
    while (1)
    {
        printf("%d %d %d %d %d \n", read_lsa().lsa_read[0], read_lsa().lsa_read[2], read_lsa().lsa_read[1], read_lsa().lsa_read[4],read_lsa().lsa_read[3]);
        vTaskDelay(10 / portTICK_RATE_MS);
    }
}
