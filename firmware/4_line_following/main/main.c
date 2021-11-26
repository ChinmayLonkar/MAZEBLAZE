#include "mazeblaze.h"
#include "tuning_http_server.h"

void app_main()
{
    ESP_ERROR_CHECK(enable_lsa());

    while (1)
    {
        int optimum_duty_cycle = 63;
        int lower_duty_cycle = 50;
        int higher_duty_cycle = 76;
        int duty_cycle = 60;
        // int kp = 1, kd = 0, ki = 0;
        unsigned int prev_position = 0;
        long cumulative_position = 0;
        int current_position = ((int)position().pos) - 100;
        //500 300 100 -100 -300
        int position_rate = current_position - prev_position;
        cumulative_position += current_position;
        const int max = 60;
        if (cumulative_position > max)
            cumulative_position = max;
        if (cumulative_position < -max)
            cumulative_position = -max;
        int correction_speed = read_pid_const().kp * current_position + read_pid_const().kd * position_rate + read_pid_const().ki * cumulative_position;
        duty_cycle = bound((optimum_duty_cycle + correction_speed), lower_duty_cycle, higher_duty_cycle);
        if (position().pos < 0)
        {
            set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, duty_cycle + correction_speed);
            set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, duty_cycle);
            vTaskDelay(100 / portTICK_RATE_MS);
        }
        else
        {
            set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, duty_cycle);
            set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, duty_cycle + correction_speed);
            vTaskDelay(100 / portTICK_RATE_MS);
        }

        prev_position = current_position;

        if (position().pos == 500) // OnlyLeft
        {
            set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
            set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
            vTaskDelay(100 / portTICK_RATE_MS);
            set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, -duty_cycle);
            set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, duty_cycle);
            vTaskDelay(100 / portTICK_RATE_MS);
        }
        if (position().pos == -300) // OnlyRight
        {
            set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
            set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
            vTaskDelay(100 / portTICK_RATE_MS);
            set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, -duty_cycle);
            set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, duty_cycle);
            vTaskDelay(100 / portTICK_RATE_MS);
        }
        if (position().pos == 300) // Plus
        {
            set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
            set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
            vTaskDelay(100 / portTICK_RATE_MS);
            set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, -duty_cycle);
            set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, duty_cycle);
            vTaskDelay(100 / portTICK_RATE_MS);
        }
        if (position().pos == 200) // T
        {
            set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
            set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
            vTaskDelay(100 / portTICK_RATE_MS);
            set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, -duty_cycle);
            set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, duty_cycle);
            vTaskDelay(100 / portTICK_RATE_MS);
        }
        if (position().pos == -200) // Straight+Right
        {
            set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
            set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
            vTaskDelay(100 / portTICK_RATE_MS);
            set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, -duty_cycle);
            set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, duty_cycle);
            vTaskDelay(100 / portTICK_RATE_MS);
        }
        if (position().pos == 600) // Straight+Left
        {
            set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
            set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
            vTaskDelay(100 / portTICK_RATE_MS);
            set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, -duty_cycle);
            set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, duty_cycle);
            vTaskDelay(100 / portTICK_RATE_MS);
        }
        if (position().pos == 0) // DeadEnd
        {
            set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
            set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
            vTaskDelay(100 / portTICK_RATE_MS);
            set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, -duty_cycle);
            set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, duty_cycle);
            vTaskDelay(100 / portTICK_RATE_MS);
        }
    }
}
