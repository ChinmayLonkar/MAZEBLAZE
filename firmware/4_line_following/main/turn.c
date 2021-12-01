#include "turn.h"

TaskHandle_t task_straight = NULL;
int optimum_duty_cycle = 80;
int lower_duty_cycle = 70;
int higher_duty_cycle = 80;
int duty_cycle = 75;
int correction_speed;
void straight()
{
    while (1)
    {
        // int kp = 1, kd = 0, ki = 0;
        unsigned int prev_position = 0;
        long cumulative_position = 0;
        int current_position = ((int)position().pos) - 100;
        //500 300 100 -100 -300
        int position_rate = current_position - prev_position;
        cumulative_position += current_position;
        const int max = 50;
        if (cumulative_position > max)
            cumulative_position = max;
        if (cumulative_position < -max)
            cumulative_position = -max;
        correction_speed = read_pid_const().kp * current_position + read_pid_const().kd * position_rate + read_pid_const().ki * cumulative_position;
        duty_cycle = bound((optimum_duty_cycle - correction_speed), lower_duty_cycle, higher_duty_cycle);
        if (current_position == 0)
        {
            set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, duty_cycle);
            set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, duty_cycle);
        }
        else if (current_position < 0) // Right on the line
        {
            set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, duty_cycle + correction_speed);
            set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, duty_cycle);
        }
        else if (current_position > 0)
        {
            set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, duty_cycle);
            set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, duty_cycle + correction_speed);
        }
        ESP_LOGI("debug", "KP: %f ::  KI: %f  :: KD: %f :: POS: %d :: CS: %d", read_pid_const().kp, read_pid_const().ki, read_pid_const().kd, position().pos,correction_speed);

    }
    vTaskDelete(NULL);
}

void turn(int direction)
{
    if (task_straight != NULL)
    {
        vTaskDelete(task_straight);
        task_straight = NULL;
    }

    stop();
    if (direction == RIGHT)
    {
        set_motor_speed(MOTOR_A_0, MOTOR_BACKWARD, duty_cycle);
        set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, duty_cycle);
        vTaskDelay(100 / portTICK_RATE_MS);
    }
    else if (direction == LEFT)
    {
        set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, duty_cycle);
        set_motor_speed(MOTOR_A_1, MOTOR_BACKWARD, duty_cycle);
        vTaskDelay(100 / portTICK_RATE_MS);
    }
    else if (direction == UTURN)
    {
        set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, duty_cycle);
        set_motor_speed(MOTOR_A_1, MOTOR_BACKWARD, duty_cycle);
        vTaskDelay(200 / portTICK_RATE_MS);
    }
    go_straight();
}

void stop()
{
    set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);
    set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
}

void go_straight()
{
    if (task_straight == NULL)
    {
        xTaskCreate(&straight, "Straight", 4096, NULL, 1, &task_straight);
    }
}