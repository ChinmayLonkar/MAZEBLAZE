#include "mazeblaze.h"
#include "tuning_http_server.h"
#include "line_following.h"
#include "node_detection.h"
#include "turn.h"
#include "esp_err.h"
#include "wifi_logger.h"

void maze_explore(void *arg)
{

    while (1)
    {
        if (only_straight())
        {
            go_straight();
        }
        else if (only_left())
        {
            turn(LEFT);
        }
        else if (only_right())
        {
            turn(RIGHT);
        }

        else if (plus_node())
        {
            turn(LEFT);
        }

        else if (T_node())
        {
            turn(LEFT);
        }

        else if (straight_right())
        {
            go_straight();
        }

        else if (straight_left())
        {
            turn(LEFT);
        }

        else if (deadend())
        {
            turn(UTURN);
        }

        else if (end())
        {
            stop();
            vTaskDelete(NULL);
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    ESP_ERROR_CHECK(enable_lsa());
    ESP_ERROR_CHECK(enable_motor_driver());
    start_wifi_logger(); // Start wifi logger
    xTaskCreate(&start_tuning_http_server,"start server",4096,NULL,1,NULL);
    xTaskCreate(&maze_explore,"maze explore",4096,NULL,1,NULL);
    
}