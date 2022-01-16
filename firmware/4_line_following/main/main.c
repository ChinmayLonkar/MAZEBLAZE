// // #include "mazeblaze.h"
// #include "tuning_http_server.h"
#include "line_following.h"
#include "node_detection.h"
#include "turn.h"
// #include "esp_err.h"
// #include "wifi_logger.h"

// #define TAG "LEFT_FOLLOW"

// void maze_explore(void *arg)
// {

//     while (1)
//     {
//         if (only_straight())
//         {
//             ESP_LOGI(TAG, "Only Straight Path Detected");
//             go_straight();
//         }

//         else if (only_left())
//         {
//             ESP_LOGI(TAG, "Only Left Path Detected");
//             turn(LEFT);

//         }
//         else if (only_right())
//         {
//             ESP_LOGI(TAG, "Only Right Path Detected");
//             turn(RIGHT);

//         }

//         else if (plus_node())
//         {
//             ESP_LOGI(TAG, "Plus Path Detected");
//             turn(LEFT);

//         }

//         else if (T_node())
//         {
//             ESP_LOGI(TAG, "T Path Detected");
//             turn(LEFT);

//         }

//         else if (straight_right())
//         {
//             ESP_LOGI(TAG, "Straight Right Path Detected");

//         }

//         else if (straight_left())
//         {
//             ESP_LOGI(TAG, "Straight Left Path Detected");
//             turn(LEFT);

//         }

//         // else if (deadend())
//         // {
//         //     ESP_LOGI(TAG, "Deadend Path Detected");
//         //     turn(UTURN);
//         // }

//         else if (end())
//         {
//             ESP_LOGI(TAG, "End Path Detected");
//             stop();
//             vTaskDelete(NULL);
//         }
//         else {
//             ESP_LOGI(TAG, "Went into last else loop, look into this condition POS :- %d",position().pos);
//             // stop();
//         }

//         vTaskDelay(10 / portTICK_PERIOD_MS);
//     }
// }

// void app_main()
// {
//     ESP_ERROR_CHECK(enable_lsa());
//     ESP_ERROR_CHECK(enable_motor_driver());
//     start_wifi_logger(); // Start wifi logger
//     xTaskCreate(&start_tuning_http_server, "start server", 4096, NULL, 1, NULL);
//     xTaskCreate(&maze_explore, "maze explore", 4096, NULL, 1, NULL);
// }

#include "mazeblaze.h"
#include "line_following.h"

void app_main(void)
{
    ESP_ERROR_CHECK(enable_lsa());
    ESP_ERROR_CHECK(enable_motor_driver());
    gpio_pad_pullup(33);
    gpio_pad_pullup(12);
    while (1)
    {
        printf("%d %d %d %d %d \n", read_lsa().lsa_read[4], read_lsa().lsa_read[3], read_lsa().lsa_read[2], read_lsa().lsa_read[1], read_lsa().lsa_read[0]);
        if ((position().pos < 500 && position().pos > -300 && position().pos != 0 && position().pos != 300 && position().pos != 200 && position().pos != -300 && position().pos != 500 && position().pos != 600 && position().pos != -200 && position().pos != -400 && position().pos != 800) || (straight_right()))
        {
            int left_duty_cycle;
            int duty_cycle = 80;
            int right_duty_cycle;
            int correction_speed;

            // int kp = 1, kd = 0, ki = 0;
            unsigned int prev_position = 0;
            long cumulative_position = 0;
            int current_position = ((int)position().pos) - 100;
            int position_rate = current_position - prev_position;
            cumulative_position += current_position;
            const int max = 25;
            if (cumulative_position > max)
                cumulative_position = max;
            if (cumulative_position < -max)
                cumulative_position = -max;
            correction_speed = read_pid_const().kp * current_position + read_pid_const().kd * position_rate + read_pid_const().ki * cumulative_position;
            // duty_cycle = bound((optimum_duty_cycle - correction_speed), lower_duty_cycle, higher_duty_cycle);
            left_duty_cycle = duty_cycle + correction_speed;
            right_duty_cycle = duty_cycle - correction_speed;
            if (current_position == 0)
            {
                set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, left_duty_cycle);
                set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, right_duty_cycle);
                // vTaskDelay(10 / portTICK_PERIOD_MS);
            }
            else if (current_position < 0) // Right on the line
            {
                set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, left_duty_cycle);
                set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, right_duty_cycle);
                // vTaskDelay(10 / portTICK_PERIOD_MS);
            }
            else if (current_position > 0)
            {
                set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, left_duty_cycle);
                set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, right_duty_cycle);
                // vTaskDelay(10 / portTICK_PERIOD_MS);
            }
        //  ESP_LOGI("debug", "KP: %f ::  KI: %f  :: KD: %f :: POS: %d :: CS: %d :: LD: %d :: RD: %d", read_pid_const().kp, read_pid_const().ki, read_pid_const().kd, position().pos, correction_speed, left_duty_cycle, right_duty_cycle);

        }
        // if (read_lsa().lsa_read[2] == 100 && read_lsa().lsa_read[4] != 100 && read_lsa().lsa_read[3] != 100 && read_lsa().lsa_read[1] != 100 && read_lsa().lsa_read[0] != 100)
        // {
        //     set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, 75);
        //     set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 75);
        //     vTaskDelay(100 / portTICK_RATE_MS);
        //     // set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 100);
        //     // set_motor_speed(MOTOR_A_0, MOTOR_BACKWARD, 100);
        //     // vTaskDelay(1000/portTICK_RATE_MS);
        //     // set_motor_speed(MOTOR_A_0, MOTOR_STOP, 100);
        //     // set_motor_speed(MOTOR_A_1, MOTOR_STOP, 100);
        //     // vTaskDelay(1000/portTICK_RATE_MS);
        // }
        else if ((read_lsa().lsa_read[4] == 100 && read_lsa().lsa_read[2] != 100 && read_lsa().lsa_read[3] != 100 && read_lsa().lsa_read[1] != 100 && read_lsa().lsa_read[0] != 100) || (plus_node()) || (T_node()) || (straight_left()))
        {
            set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, 70);
            set_motor_speed(MOTOR_A_1, MOTOR_BACKWARD, 70);
            vTaskDelay(60 / portTICK_RATE_MS);
            // set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 100);
            // set_motor_speed(MOTOR_A_0, MOTOR_BACKWARD, 100);
            // vTaskDelay(1000/portTICK_RATE_MS);
            // set_motor_speed(MOTOR_A_0, MOTOR_STOP, 100);
            // set_motor_speed(MOTOR_A_1, MOTOR_STOP, 100);
            // vTaskDelay(1000/portTICK_RATE_MS);
        }
        else if (read_lsa().lsa_read[0] == 100 && read_lsa().lsa_read[4] != 100 && read_lsa().lsa_read[3] != 100 && read_lsa().lsa_read[2] != 100 && read_lsa().lsa_read[1] != 100)
        {
            set_motor_speed(MOTOR_A_0, MOTOR_BACKWARD, 70);
            set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 70);
            vTaskDelay(60 / portTICK_RATE_MS);
            // set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, 100);
            // set_motor_speed(MOTOR_A_0, MOTOR_BACKWARD, 100);
            // vTaskDelay(1000/portTICK_RATE_MS);
            // set_motor_speed(MOTOR_A_0, MOTOR_STOP, 100);
            // set_motor_speed(MOTOR_A_1, MOTOR_STOP, 100);
            // vTaskDelay(1000/portTICK_RATE_MS);
        }
        else
        {
            set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
            set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
        }

        vTaskDelay(100 / portTICK_RATE_MS);
    }
}
