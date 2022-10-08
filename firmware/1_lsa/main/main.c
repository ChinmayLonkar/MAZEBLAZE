
#include "mazeblaze.h"

void app_main(void)
{
    ESP_ERROR_CHECK(enable_lsa());
    ESP_ERROR_CHECK(enable_motor_driver());
   
    while (1)
    {
        printf("%d %d %d %d %d \n", read_lsa().data[0], read_lsa().data[1], read_lsa().data[2], read_lsa().data[3],read_lsa().data[4]);
        vTaskDelay(10 / portTICK_RATE_MS);
    }
}
