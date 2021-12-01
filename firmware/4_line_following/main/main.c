#include "mazeblaze.h"
#include "tuning_http_server.h"
#include "line_following.h"
#include "node_detection.h"
#include "turn.h"
#include "esp_log.h"
#include "esp_err.h"
#include "wifi_logger.h"

void maze_explore(void *arg)
{
    ESP_ERROR_CHECK(enable_lsa());
    ESP_ERROR_CHECK(enable_motor_driver());

    while (1)
    {
        if (only_straight())
        {
            go_straight();
        }
        // else if (only_left())
        // {
        //     turn(LEFT);
        // }
        // else if (only_right())
        // {
        //     turn(RIGHT);
        // }

        // else if (plus_node())
        // {
        //     turn(LEFT);
        // }

        // else if (T_node())
        // {
        //     turn(LEFT);
        // }

        // else if (straight_right())
        // {
        //     go_straight();
        // }

        // else if (straight_left())
        // {
        //     turn(LEFT);
        // }

        // else if (deadend())
        // {
        //     turn(UTURN);
        // }

        // else if (end())
        // {
        //     stop();
        // }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    // xTaskCreate(&maze_explore, "maze_explore", 4096, NULL, 1, NULL);
    start_wifi_logger(); // Start wifi logger
    start_tuning_http_server();
    while (1)
    {
        wifi_log_e("test", "%s %d %f", "hello world wifi logger", 43, 45.341223242); // write log over wifi with log level -> ERROR
        vTaskDelay(10);
    }
}