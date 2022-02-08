#include "mazeblaze.h"
#include "tuning_http_server.h"
#include "line_following.h"
#include "node_detection.h"
#include "turn.h"
#include "esp_err.h"
#include "wifi_logger.h"
bool endl = true;
int prev;
void maze_explore(void *arg)
{

    while (1)
    {
        if (only_straight() || straight_right())
        {
            set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, 62);
            set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 62);
            vTaskDelay(200 / portTICK_PERIOD_MS);

            if (read_lsa().data[2] == 1)
            {
                take_turn(STRAIGHT);
                prev = STRAIGHT;
                vTaskSuspend(Maze_explore);
            }
            else
            {
                take_turn(RIGHT);
                prev = RIGHT;
                vTaskSuspend(Maze_explore);
            }
        }
        else if (only_left() || plus_node() || T_node() || straight_left())
        {
            if((prev != LEFT) || (prev != RIGHT)){
            take_turn(LEFT);
            prev = LEFT;
            vTaskSuspend(Maze_explore);
            }else{
                take_turn(STRAIGHT);
                prev = STRAIGHT;
                vTaskSuspend(Maze_explore);
            }
        }
        else if (only_right())
        {
            if((prev != LEFT) || (prev != RIGHT)){
            take_turn(RIGHT);
            prev = RIGHT;
            vTaskSuspend(Maze_explore);
            }else{
                take_turn(STRAIGHT);
                prev = STRAIGHT;
                vTaskSuspend(Maze_explore);
            }
        }
        else if (deadend())
        {
            take_turn(UTURN);
            prev = LEFT;
        }
        else if (end())
        {
            stop();
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    ESP_ERROR_CHECK(enable_lsa());
    ESP_ERROR_CHECK(enable_motor_driver());
    // start_wifi_logger(); // Start wifi logger

    if (endl)
    { // xTaskCreate(&start_tuning_http_server,"start server",4096,NULL,1,NULL);
        xTaskCreate(&maze_explore, "maze explore", 4096, NULL, 1, &Maze_explore);
    }
}