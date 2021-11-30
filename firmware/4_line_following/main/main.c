#include "mazeblaze.h"
#include "tuning_http_server.h"
#include "line_following.h"
#include "node_detection.h"
#include "turn.h"

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
        }
    }
}

void app_main()
{
    xTaskCreate(&maze_explore, "maze_explore", 4096, NULL, 1, NULL);
    start_tuning_http_server();
}